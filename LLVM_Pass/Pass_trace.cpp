#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

struct MyInstrPass : public PassInfoMixin<MyInstrPass> {
  bool isFuncLogger(StringRef name) { return name == "instrLogger"; }

  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    for (auto &F : M) {
      if (isFuncLogger(F.getName()) || F.isDeclaration())
        continue;

      for (auto &B : F) {
        for (auto &I : B) {
          if (llvm::isa<llvm::PHINode>(I))
            continue;

          // Prepare builder for IR modification
          LLVMContext &Ctx = F.getContext();
          IRBuilder<> builder(Ctx);
          Type *retType = Type::getVoidTy(Ctx);
          Type *int8PtrTy = PointerType::get(Type::getInt8Ty(Ctx), 0);

          // Prepare instrLogger function
          ArrayRef<Type *> funcInstrParamTypes = {int8PtrTy, int8PtrTy};
          FunctionType *funcInstrLogFuncType =
              FunctionType::get(retType, funcInstrParamTypes, false);
          FunctionCallee funcInstrLogFunc =
              M.getOrInsertFunction("instrLogger", funcInstrLogFuncType);

          // Insert a call to instrLogger function before each instruction,
          // except phi
          insertLoggerCall(builder, I, &I, funcInstrLogFunc);
        }
      }
    }

    outs() << "\n";
    return PreservedAnalyses::none();
  }

  void insertLoggerCall(IRBuilder<> &builder, Instruction &I, Instruction *uses,
                        FunctionCallee &f) {
    for (Use &U : uses->operands()) {
      Value *operand = U.get();

      if (auto *USES = dyn_cast<Instruction>(operand)) {
        builder.SetInsertPoint(&I);
        Value *userName = builder.CreateGlobalStringPtr(I.getOpcodeName());
        if (llvm::isa<llvm::PHINode>(USES)) {
          insertLoggerCall(builder, I, USES, f);
        } else {
          Value *usesName =
              builder.CreateGlobalStringPtr(USES->getOpcodeName());

          Value *args[] = {userName, usesName};
          builder.CreateCall(f, args);
        }
      }
    }
  }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([=](ModulePassManager &MPM, auto) {
      MPM.addPass(MyInstrPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "MyTracePlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
