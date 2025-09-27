#ifdef GETELEMENTPTR
struct S {
  int x;
  int y;
};
#endif

#ifdef BITCAST
int bitcastFromFloatToInt(float x) {
  return *(int*)&x;
}
#endif

#ifdef TAIL_CALL
int bar(int x) {
  if (x == 0)
    return 0;
  else
    return bar(x - 1) + x;
}
#endif

int main() {
  // clang main.c -emit-llvm -S -O0 -D TRUNC
  #ifdef TRUNC
  int a = 58;
  char b = a;
  #endif

  // clang main.c -emit-llvm -S -O0 -D GETELEMENTPTR
  #ifdef GETELEMENTPTR
  struct S s = {58, 58};
  int* c = &s.x;
  #endif

  // clang main.c -emit-llvm -S -O0 -D SREM
  #ifdef SREM
  int d = -137;
  int e = d % 5;
  #endif

  // clang main.c -emit-llvm -S -O0 -D LSHR
  #ifdef LSHR
  unsigned int f = 10;
  unsigned int g = 2;
  f = f >> g;
  #endif

  // clang main.c -emit-llvm -S -O0 -D ZEXT
  #ifdef ZEXT
  unsigned char h = 0;
  h = (unsigned int)h;
  #endif

  // clang main.c -emit-llvm -S -O1 -D SITOFP
  #ifdef BITCAST
  float i = 58.0;
  int j = bitcastFromFloatToInt(i);
  #endif

  // clang main.c -emit-llvm -S -O0 -D SITOFP
  #ifdef SITOFP
  int k = 58;
  float l = k;
  #endif

  // clang main.c -emit-llvm -S -O0 -D SELECT
  #ifdef SELECT
  int m = 7;
  int n = (m > 0) ? 1 : 0;
  #endif

  // clang main.c -emit-llvm -S -O0 -D FPEXT
  #ifdef FPEXT
  float o = 0;
  double p = o;
  #endif

  // clang main.c -emit-llvm -S -O1 -D TAIL_CALL
  #ifdef TAIL_CALL
  int q = 15;
  int r = bar(q);
  #endif
}
