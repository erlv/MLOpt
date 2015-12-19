#include <stdint.h>
#include <iostream>
#include "MatrixMul/MMScalar.hpp"

using namespace std;

int int8VSfloat() {
  MMScalar<float> mmobj_float(PRE_D_M, PRE_D_N, PRE_D_K, "float");
  mmobj_float.initArray();
  mmobj_float.runWithTimer();
  MMScalar<int8_t> mmobj_char(PRE_D_M, PRE_D_N, PRE_D_K, "int8_t");
  mmobj_char.initArray();
  mmobj_char.runWithTimer();
  return 0;
}

int main() {
  int8VSfloat();
  return 0;
}
