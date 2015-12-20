#include <cstdint>
#include <iostream>
#include "MatrixMul/MMScalar.hpp"
#include "MatrixMul/MMNeon.hpp"

using namespace std;

int int8NeonVSint8() {
  MMScalar<int8_t> mmobj_char(PRE_D_M, PRE_D_N, PRE_D_K, "int8_t");
  mmobj_char.initArray();
  mmobj_char.runWithTimer();

  MMInt8Neon mmobj_neonchar(PRE_D_M, PRE_D_N, PRE_D_K);
  mmobj_neonchar.initArray();
  mmobj_neonchar.runWithTimer();
  mmobj_neonchar.verifyResult();
  return 0;
}

int int8NeonVSint8mini() {

  MMInt8Neon mmobj_neonchar(PRE_D_M, PRE_D_N, PRE_D_K);
  mmobj_neonchar.initArray();
  mmobj_neonchar.fastMode();
  mmobj_neonchar.runWithTimer();
  mmobj_neonchar.verifyResult();
  return 0;
}

int main() {
  //int8NeonVSint8();
  int8NeonVSint8mini();

  return 0;
}
