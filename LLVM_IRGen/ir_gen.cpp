#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <system_error>

#include "sim.h"
using namespace llvm;

class IRGenerator final {
    LLVMContext context;
    IRBuilder<> builder;
    Module* module;

    Function *lifetimeStartFunc = nullptr;
    Function *lifetimeEndFunc = nullptr;
    Function *memsetFunc = nullptr;
    Function *memcpyFunc = nullptr;
    Function *simRandFunc = nullptr;
    Function *fillRectFunc = nullptr;
    Function *simFlushFunc = nullptr;
    Function *GenerateStartPositionFunc = nullptr;
    Function *paintXYFunc = nullptr;
    Function *countNeighboursFunc = nullptr;
    Function *NextStepFunc = nullptr;
    Function *DrawFieldFunc = nullptr;
    Function *appFunc = nullptr;

    void generateBuiltIn() {
        FunctionType *lifetimeStartType = FunctionType::get(
            Type::getVoidTy(context),
            {builder.getInt64Ty(), PointerType::get(builder.getInt8Ty(), 0)},
            false
        );
        lifetimeStartFunc = Function::Create(lifetimeStartType, Function::ExternalLinkage, "llvm.lifetime.start.p0", module);
        lifetimeEndFunc = Function::Create(lifetimeStartType, Function::ExternalLinkage, "llvm.lifetime.end.p0", module);

        FunctionType *memsetType = FunctionType::get(
            Type::getVoidTy(context),
            {PointerType::get(builder.getInt8Ty(), 0), builder.getInt8Ty(), builder.getInt64Ty(), builder.getInt1Ty()},
            false
        );
        memsetFunc = Function::Create(memsetType, Function::ExternalLinkage, "llvm.memset.p0.i64", module);

        FunctionType *memcpyType = FunctionType::get(
            Type::getVoidTy(context),
            {PointerType::get(builder.getInt8Ty(), 0), PointerType::get(builder.getInt8Ty(), 0), builder.getInt64Ty(), builder.getInt1Ty()},
            false
        );
        memcpyFunc = Function::Create(memcpyType, Function::ExternalLinkage, "llvm.memcpy.p0.p0.i64", module);
    }

    void generateExternalFunc() {
        FunctionType *simRandType = FunctionType::get(builder.getInt32Ty(), true);
        simRandFunc = Function::Create(simRandType, Function::ExternalLinkage, "simRand", module);

        FunctionType *fillRectType = FunctionType::get(
            Type::getVoidTy(context),
            {builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty(), builder.getInt32Ty()},
            false
        );
        fillRectFunc = Function::Create(fillRectType, Function::ExternalLinkage, "fillRect", module);

        FunctionType *simFlushType = FunctionType::get(Type::getVoidTy(context), true);
        simFlushFunc = Function::Create(simFlushType, Function::ExternalLinkage, "simFlush", module);
    }

    void generateGenerateStartPosition() {
        FunctionType *GenerateStartPositionType = FunctionType::get(
            Type::getVoidTy(context),
            {PointerType::get(builder.getInt32Ty(), 0)},
            false
        );
        
        GenerateStartPositionFunc = Function::Create(
            GenerateStartPositionType,
            Function::ExternalLinkage,
            "GenerateStartPosition",
            module
        );
        
        GenerateStartPositionFunc->setDSOLocal(true);
        
        BasicBlock *label1 = BasicBlock::Create(context, "entry", GenerateStartPositionFunc);
        BasicBlock *label2 = BasicBlock::Create(context, "2", GenerateStartPositionFunc);
        BasicBlock *label3 = BasicBlock::Create(context, "3", GenerateStartPositionFunc);
        
        builder.SetInsertPoint(label1);
        builder.CreateBr(label3);


        builder.SetInsertPoint(label2);
        builder.CreateRetVoid();

        builder.SetInsertPoint(label3);
        PHINode *phi4 = builder.CreatePHI(builder.getInt64Ty(), 2, "4");
        phi4->addIncoming(builder.getInt64(0), &GenerateStartPositionFunc->getEntryBlock());
        CallInst *call5 = builder.CreateCall(simRandFunc, {}, "5");
        call5->setTailCall(true);
        Value *and6 = builder.CreateAnd(call5, builder.getInt32(1), "6");
        Argument *arg0 = &GenerateStartPositionFunc->arg_begin()[0];
        Value *gep7 = builder.CreateGEP(builder.getInt32Ty(), arg0, phi4, "7");
        StoreInst *store = builder.CreateStore(and6, gep7);
        store->setAlignment(Align(4));
        Value *add8 = builder.CreateAdd(phi4, builder.getInt64(1), "8");
        cast<Instruction>(add8)->setHasNoUnsignedWrap(true);
        cast<Instruction>(add8)->setHasNoSignedWrap(true);
        Value *icmp9 = builder.CreateICmpEQ(add8, builder.getInt64(10000), "9");
        builder.CreateCondBr(icmp9, label2, label3);
        phi4->addIncoming(add8, label3);
    }

    void generatePaintXY() {
        FunctionType *paintXYType = FunctionType::get(
            Type::getVoidTy(context),
            {builder.getInt32Ty(), builder.getInt32Ty()},
            false
        );
        paintXYFunc = Function::Create(
            paintXYType,
            Function::ExternalLinkage,
            "paintXY",
            module
        );
        paintXYFunc->setDSOLocal(true);
    
        Argument *paintXYArg0 = &paintXYFunc->arg_begin()[0];
        Argument *paintXYArg1 = &paintXYFunc->arg_begin()[1];
        BasicBlock *paintXYEntry = BasicBlock::Create(context, "entry", paintXYFunc);
        builder.SetInsertPoint(paintXYEntry);
        Value *srem3 = builder.CreateSRem(paintXYArg0, builder.getInt32(100), "3");
        Value *sdiv4 = builder.CreateSDiv(paintXYArg0, builder.getInt32(100), "4");
        Value *mul5 = builder.CreateMul(srem3, builder.getInt32(10), "5");
        Value *or6_paint = builder.CreateOr(mul5, builder.getInt32(1), "6");
        Value *mul7 = builder.CreateMul(sdiv4, builder.getInt32(10), "7");
        Value *or8_paint = builder.CreateOr(mul7, builder.getInt32(1), "8");
        builder.CreateCall(fillRectFunc, {or6_paint, or8_paint, builder.getInt32(9), builder.getInt32(9), paintXYArg1});
        builder.CreateRetVoid();
    }

    void generateCountNeighbours() {
        FunctionType *countNeighboursType = FunctionType::get(
            builder.getInt32Ty(),
            {PointerType::get(builder.getInt32Ty(), 0), builder.getInt32Ty()},
            false
        );
        countNeighboursFunc = Function::Create(
            countNeighboursType,
            Function::ExternalLinkage,
            "countNeighbours",
            module
        );
        countNeighboursFunc->setDSOLocal(true);
        Argument *countNeighboursArg0 = &countNeighboursFunc->arg_begin()[0];
        Argument *countNeighboursArg1 = &countNeighboursFunc->arg_begin()[1];


        BasicBlock *countNeighboursEntry = BasicBlock::Create(context, "entry", countNeighboursFunc);
        builder.SetInsertPoint(countNeighboursEntry);
        Value *srem3_cn = builder.CreateSRem(countNeighboursArg1, builder.getInt32(100), "3");
        Value *sdiv4_cn = builder.CreateSDiv(countNeighboursArg1, builder.getInt32(100), "4");
        Value *add5_cn = builder.CreateAdd(sdiv4_cn, builder.getInt32(99), "5");
        Value *srem6_cn = builder.CreateSRem(add5_cn, builder.getInt32(100), "6");
        Value *mul7_cn = builder.CreateMul(srem6_cn, builder.getInt32(100), "7");
        Value *add8_cn = builder.CreateAdd(sdiv4_cn, builder.getInt32(1), "8");
        Value *srem9_cn = builder.CreateSRem(add8_cn, builder.getInt32(100), "9");
        Value *mul10_cn = builder.CreateMul(srem9_cn, builder.getInt32(100), "10");
        Value *add11_cn = builder.CreateAdd(srem3_cn, builder.getInt32(99), "11");
        Value *add12_cn = builder.CreateAdd(srem3_cn, builder.getInt32(-1), "12");
        Value *icmp13_cn = builder.CreateICmpULT(add11_cn, builder.getInt32(100), "13");
        Value *select14_cn = builder.CreateSelect(icmp13_cn, add11_cn, add12_cn, "14");
        Value *trunc15_cn = builder.CreateTrunc(srem3_cn, builder.getInt8Ty(), "15");
        Value *add16_cn = builder.CreateAdd(trunc15_cn, builder.getInt8(1), "16");
        Value *srem17_cn = builder.CreateSRem(add16_cn, builder.getInt8(100), "17");
        Value *sext18_cn = builder.CreateSExt(srem17_cn, builder.getInt32Ty(), "18");
        Value *mul19_cn = builder.CreateMul(sdiv4_cn, builder.getInt32(100), "19");
        Value *add20_cn = builder.CreateAdd(mul7_cn, select14_cn, "20");
        Value *sext21_cn = builder.CreateSExt(add20_cn, builder.getInt64Ty(), "21");
        Value *gep22_cn = builder.CreateGEP(builder.getInt32Ty(), countNeighboursArg0, sext21_cn, "22");
        Value *load23_cn = builder.CreateLoad(builder.getInt32Ty(), gep22_cn, "23");
        Value *add24_cn = builder.CreateAdd(mul7_cn, srem3_cn, "24");
        Value *sext25_cn = builder.CreateSExt(add24_cn, builder.getInt64Ty(), "25");
        Value *gep26_cn = builder.CreateGEP(builder.getInt32Ty(), countNeighboursArg0, sext25_cn, "26");
        Value *load27_cn = builder.CreateLoad(builder.getInt32Ty(), gep26_cn, "27");
        Value *add28_cn = builder.CreateAdd(load27_cn, load23_cn, "28");
        Value *add29_cn = builder.CreateAdd(mul7_cn, sext18_cn, "29");
        Value *sext30_cn = builder.CreateSExt(add29_cn, builder.getInt64Ty(), "30");
        Value *gep31_cn = builder.CreateGEP(builder.getInt32Ty(), countNeighboursArg0, sext30_cn, "31");
        Value *load32_cn = builder.CreateLoad(builder.getInt32Ty(), gep31_cn, "32");
        Value *add33_cn = builder.CreateAdd(add28_cn, load32_cn, "33");
        Value *add34_cn = builder.CreateAdd(select14_cn, mul19_cn, "34");
        Value *sext35_cn = builder.CreateSExt(add34_cn, builder.getInt64Ty(), "35");
        Value *gep36_cn = builder.CreateGEP(builder.getInt32Ty(), countNeighboursArg0, sext35_cn, "36");
        Value *load37_cn = builder.CreateLoad(builder.getInt32Ty(), gep36_cn, "37");
        Value *add38_cn = builder.CreateAdd(add33_cn, load37_cn, "38");
        Value *add39_cn = builder.CreateAdd(mul19_cn, sext18_cn, "39");
        Value *sext40_cn = builder.CreateSExt(add39_cn, builder.getInt64Ty(), "40");
        Value *gep41_cn = builder.CreateGEP(builder.getInt32Ty(), countNeighboursArg0, sext40_cn, "41");
        Value *load42_cn = builder.CreateLoad(builder.getInt32Ty(), gep41_cn, "42");
        Value *add43_cn = builder.CreateAdd(add38_cn, load42_cn, "43");
        Value *add44_cn = builder.CreateAdd(mul10_cn, select14_cn, "44");
        Value *sext45_cn = builder.CreateSExt(add44_cn, builder.getInt64Ty(), "45");
        Value *gep46_cn = builder.CreateGEP(builder.getInt32Ty(), countNeighboursArg0, sext45_cn, "46");
        Value *load47_cn = builder.CreateLoad(builder.getInt32Ty(), gep46_cn, "47");
        Value *add48_cn = builder.CreateAdd(add43_cn, load47_cn, "48");
        Value *add49_cn = builder.CreateAdd(mul10_cn, srem3_cn, "49");
        Value *sext50_cn = builder.CreateSExt(add49_cn, builder.getInt64Ty(), "50");
        Value *gep51_cn = builder.CreateGEP(builder.getInt32Ty(), countNeighboursArg0, sext50_cn, "51");
        Value *load52_cn = builder.CreateLoad(builder.getInt32Ty(), gep51_cn, "52");
        Value *add53_cn = builder.CreateAdd(add48_cn, load52_cn, "53");
        Value *add54_cn = builder.CreateAdd(mul10_cn, sext18_cn, "54");
        Value *sext55_cn = builder.CreateSExt(add54_cn, builder.getInt64Ty(), "55");
        Value *gep56_cn = builder.CreateGEP(builder.getInt32Ty(), countNeighboursArg0, sext55_cn, "56");
        Value *load57_cn = builder.CreateLoad(builder.getInt32Ty(), gep56_cn, "57");
        Value *add58_cn = builder.CreateAdd(add53_cn, load57_cn, "58");
        builder.CreateRet(add58_cn);
    }

    void generateNextStepType() {
        FunctionType *NextStepType = FunctionType::get(
            Type::getVoidTy(context),
            {PointerType::get(builder.getInt32Ty(), 0)},
            false
        );
        NextStepFunc = Function::Create(NextStepType, Function::ExternalLinkage, "NextStep", module);
        NextStepFunc->setDSOLocal(true);

        BasicBlock *NextStep1 = BasicBlock::Create(context, "1", NextStepFunc);
        BasicBlock *NextStep3 = BasicBlock::Create(context, "3", NextStepFunc);
        BasicBlock *NextStep7 = BasicBlock::Create(context, "7", NextStepFunc);
        BasicBlock *NextStep11 = BasicBlock::Create(context, "11", NextStepFunc);
        BasicBlock *NextStep12 = BasicBlock::Create(context, "12", NextStepFunc);
        BasicBlock *NextStep18 = BasicBlock::Create(context, "18", NextStepFunc);

        builder.SetInsertPoint(NextStep1);
        AllocaInst *array2 = builder.CreateAlloca(ArrayType::get(builder.getInt32Ty(), 10000), nullptr, "2");
        array2->setAlignment(Align(16));
        Value *size40000 = builder.getInt64(40000);
        Value *cast2 = builder.CreatePointerCast(array2, PointerType::get(builder.getInt8Ty(), 0));
        builder.CreateCall(lifetimeStartFunc, {size40000, cast2});
        Value *zero = builder.getInt8(0);
        builder.CreateCall(memsetFunc, {cast2, zero, size40000, builder.getFalse()});
        builder.CreateBr(NextStep3);

        builder.SetInsertPoint(NextStep3);
        PHINode *phi4_next = builder.CreatePHI(builder.getInt64Ty(), 2, "4");
        phi4_next->addIncoming(builder.getInt64(0), NextStep1);
        Value *trunc5 = builder.CreateTrunc(phi4_next, builder.getInt32Ty(), "5");
        CallInst *call6 = builder.CreateCall(countNeighboursFunc, {&NextStepFunc->arg_begin()[0], trunc5}, "6");
        SwitchInst *switchInst = builder.CreateSwitch(call6, NextStep11, 2);
        switchInst->addCase(builder.getInt32(3), NextStep12);
        switchInst->addCase(builder.getInt32(2), NextStep7);    
        
        builder.SetInsertPoint(NextStep7);
        Value *gep8 = builder.CreateGEP(builder.getInt32Ty(), &NextStepFunc->arg_begin()[0], phi4_next, "8");
        Value *load9 = builder.CreateLoad(builder.getInt32Ty(), gep8, "9");
        Value *icmp10 = builder.CreateICmpEQ(load9, builder.getInt32(1), "10");
        builder.CreateBr(NextStep12);
        
        builder.SetInsertPoint(NextStep11);
        builder.CreateBr(NextStep12);
        
        builder.SetInsertPoint(NextStep12);
        PHINode *phi13 = builder.CreatePHI(builder.getInt1Ty(), 3, "13");
        phi13->addIncoming(builder.getTrue(), NextStep3);
        phi13->addIncoming(icmp10, NextStep7);
        phi13->addIncoming(builder.getFalse(), NextStep11);
        Value *zext14 = builder.CreateZExt(phi13, builder.getInt32Ty(), "14");
        Value *gep15 = builder.CreateGEP(ArrayType::get(builder.getInt32Ty(), 10000), array2, {builder.getInt64(0), phi4_next}, "15");
        builder.CreateStore(zext14, gep15);
        Value *add16 = builder.CreateAdd(phi4_next, builder.getInt64(1), "16");
        Value *icmp17 = builder.CreateICmpEQ(add16, builder.getInt64(10000), "17");
        builder.CreateCondBr(icmp17, NextStep18, NextStep3);
        phi4_next->addIncoming(add16, NextStep12);
        
        builder.SetInsertPoint(NextStep18);
        Value *cast0 = builder.CreatePointerCast(&NextStepFunc->arg_begin()[0], PointerType::get(builder.getInt8Ty(), 0));
        Value *cast2_8 = builder.CreatePointerCast(array2, PointerType::get(builder.getInt8Ty(), 0));
        builder.CreateCall(memcpyFunc, {cast0, cast2_8, size40000, builder.getFalse()});
        builder.CreateCall(lifetimeEndFunc, {size40000, cast2});
        builder.CreateRetVoid();
    }

    void generateDrawField() {
        FunctionType *DrawFieldType = FunctionType::get(
            Type::getVoidTy(context),
            {PointerType::get(builder.getInt32Ty(), 0)},
            false
        );
        DrawFieldFunc = Function::Create(DrawFieldType, Function::ExternalLinkage, "DrawField", module);
        DrawFieldFunc->setDSOLocal(true);
    
        BasicBlock *DrawField1 = BasicBlock::Create(context, "1", DrawFieldFunc);
        BasicBlock *DrawField2 = BasicBlock::Create(context, "2", DrawFieldFunc);
        BasicBlock *DrawField3 = BasicBlock::Create(context, "3", DrawFieldFunc);
        
        builder.SetInsertPoint(DrawField1);
        builder.CreateBr(DrawField3);        

        builder.SetInsertPoint(DrawField2);
        builder.CreateRetVoid();
    
        builder.SetInsertPoint(DrawField3);
        PHINode *phi4_df = builder.CreatePHI(builder.getInt64Ty(), 2, "4");
        phi4_df->addIncoming(builder.getInt64(0), DrawField1);
        Value *gep5 = builder.CreateGEP(builder.getInt32Ty(), &DrawFieldFunc->arg_begin()[0], phi4_df, "5");
        Value *load6 = builder.CreateLoad(builder.getInt32Ty(), gep5, "6");
        Value *icmp7 = builder.CreateICmpEQ(load6, builder.getInt32(0), "7");
        Value *trunc8 = builder.CreateTrunc(phi4_df, builder.getInt16Ty(), "8");
        Value *urem9 = builder.CreateURem(trunc8, builder.getInt16(100), "9");
        Value *udiv10 = builder.CreateUDiv(trunc8, builder.getInt16(100), "10");
        Value *mul11 = builder.CreateMul(urem9, builder.getInt16(10), "11");
        Value *or12 = builder.CreateOr(mul11, builder.getInt16(1), "12");
        Value *zext13 = builder.CreateZExt(or12, builder.getInt32Ty(), "13");
        Value *mul14 = builder.CreateMul(udiv10, builder.getInt16(10), "14");
        Value *or15 = builder.CreateOr(mul14, builder.getInt16(1), "15");
        Value *zext16 = builder.CreateZExt(or15, builder.getInt32Ty(), "16");
        Value *select17 = builder.CreateSelect(icmp7, builder.getInt32(-1), builder.getInt32(-16764058), "17");
        builder.CreateCall(fillRectFunc, {zext13, zext16, builder.getInt32(9), builder.getInt32(9), select17});
        Value *add18 = builder.CreateAdd(phi4_df, builder.getInt64(1), "18");
        Value *icmp19 = builder.CreateICmpEQ(add18, builder.getInt64(10000), "19");
        builder.CreateCondBr(icmp19, DrawField2, DrawField3);
        phi4_df->addIncoming(add18, DrawField3);
    }

    void generateApp() {
        FunctionType *appType = FunctionType::get(Type::getVoidTy(context), false);
        appFunc = Function::Create(appType, Function::ExternalLinkage, "app", module);
        appFunc->setDSOLocal(true);
    
        BasicBlock *app0 = BasicBlock::Create(context, "0", appFunc);
        BasicBlock *app2 = BasicBlock::Create(context, "2", appFunc);
        BasicBlock *app9 = BasicBlock::Create(context, "9", appFunc);
        BasicBlock *app10 = BasicBlock::Create(context, "10", appFunc);
        
        builder.SetInsertPoint(app0);
        AllocaInst *array1 = builder.CreateAlloca(ArrayType::get(builder.getInt32Ty(), 10000), nullptr, "1");
        array1->setAlignment(Align(16));
    
        Value *cast1 = builder.CreatePointerCast(array1, PointerType::get(builder.getInt8Ty(), 0));
        Value *size40000 = builder.getInt64(40000);
        builder.CreateCall(lifetimeStartFunc, {size40000, cast1});
        Value *zero = builder.getInt8(0);
        builder.CreateCall(memsetFunc, {cast1, zero, size40000, builder.getFalse()});
        builder.CreateBr(app2);
    
        builder.SetInsertPoint(app2);
        PHINode *phi3 = builder.CreatePHI(builder.getInt64Ty(), 2, "3");
        phi3->addIncoming(builder.getInt64(0), app0);
        CallInst *call4 = builder.CreateCall(simRandFunc, {}, "4");
        Value *and5 = builder.CreateAnd(call4, builder.getInt32(1), "5");
        Value *gep6 = builder.CreateGEP(ArrayType::get(builder.getInt32Ty(), 10000), array1, {builder.getInt64(0), phi3}, "6");
        builder.CreateStore(and5, gep6);
        Value *add7 = builder.CreateAdd(phi3, builder.getInt64(1), "7");
        Value *icmp8 = builder.CreateICmpEQ(add7, builder.getInt64(10000), "8");
        builder.CreateCondBr(icmp8, app10, app2);
        phi3->addIncoming(add7, app2);
        
        builder.SetInsertPoint(app9);
        builder.CreateCall(lifetimeEndFunc, {size40000, cast1});
        builder.CreateRetVoid();
        
        builder.SetInsertPoint(app10);
        PHINode *phi11 = builder.CreatePHI(builder.getInt32Ty(), 2, "11");
        phi11->addIncoming(builder.getInt32(0), app2);
        Value *cast1_10 = builder.CreatePointerCast(array1, PointerType::get(builder.getInt32Ty(), 0));
        builder.CreateCall(DrawFieldFunc, {cast1_10});
        builder.CreateCall(NextStepFunc, {cast1_10});
        builder.CreateCall(simFlushFunc, {});
        Value *add12 = builder.CreateAdd(phi11, builder.getInt32(1), "12");
        Value *icmp13 = builder.CreateICmpEQ(add12, builder.getInt32(10000), "13");
        builder.CreateCondBr(icmp13, app9, app10);
        phi11->addIncoming(add12, app10);
    }

    public:
    IRGenerator() : context(), builder(context){
        module = new Module("../SDL/app.c", context);
    }
    ~IRGenerator() {
        delete module;
    }
    void generate() {
        generateBuiltIn();
        generateExternalFunc();
        generateGenerateStartPosition();
        generatePaintXY();
        generateCountNeighbours();
        generateNextStepType();
        generateDrawField();
        generateApp();
    }

    void dump() {
        module->print(outs(), nullptr);
        outs() << '\n';
    }

    void verify() {
        bool verif = verifyModule(*module, &outs());
        outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");   
    }

    void interpret() {
        outs() << "[EE] Run\n";
        InitializeNativeTarget();
        InitializeNativeTargetAsmPrinter();
    
        ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
        ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
            if (fnName == "simFlush") {
              return reinterpret_cast<void *>(simFlush);
            } else if (fnName == "simRand") {
              return reinterpret_cast<void *>(simRand);
            } else if (fnName == "fillRect") {
              return reinterpret_cast<void *>(fillRect);
            }
            return nullptr;
          });
        ee->finalizeObject();
        simInit();
        ArrayRef<GenericValue> noargs;
        GenericValue v = ee->runFunction(appFunc, noargs);
        simExit();
    }
};

int main(int argc, char **argv) {
    IRGenerator ir_gen;

    ir_gen.generate();
    ir_gen.dump();
    ir_gen.verify();
    ir_gen.interpret();

    return 0;
}
