#include <cstdint>
#include <iostream>
#include "MatrixMul/MMScalar.hpp"
#include "MatrixMul/MMSSE.hpp"

using namespace std;

int int8SSEVSint8() {
  MMScalar<int8_t> mmobj_char(PRE_D_M, PRE_D_N, PRE_D_K, "int8_t");
  mmobj_char.initArray();
  mmobj_char.runWithTimer();

  MMInt8SSE mmobj_ssechar(PRE_D_M, PRE_D_N, PRE_D_K);
  mmobj_ssechar.initArray();
  mmobj_ssechar.runWithTimer();
  mmobj_ssechar.verifyResult();
  return 0;
}

int int8SSEVSint8mini() {

  MMInt8SSE mmobj_ssechar(PRE_D_M, PRE_D_N, PRE_D_K);
  mmobj_ssechar.initArray();
  mmobj_ssechar.fastMode();
  mmobj_ssechar.runWithTimer();
  mmobj_ssechar.verifyResult();
  return 0;
}

int main() {
  //int8SSEVSint8();
  int8SSEVSint8mini();

  return 0;
}
