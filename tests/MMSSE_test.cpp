#include <cstdint>
#include <iostream>
#include "MatrixMul/MMScalar.hpp"
#include "MatrixMul/MMSSE.hpp"

using namespace std;

int int8SSEVSint8() {
  MMScalar<int8_t> mmobj_char(512,1, 2048, "int8_t");
  mmobj_char.runWithTimer();

  MMInt8SSE mmobj_ssechar(512, 1, 2048);
  mmobj_ssechar.runWithTimer();
  mmobj_ssechar.verifyResult();
  return 0;
}

int int8SSEVSint8mini() {
#if 0
  MMScalar<int8_t> mmobj_char(16, 1, 32, "int8_tmini");
  mmobj_char.fastMode();
  mmobj_char.runWithTimer();
#endif

  MMInt8SSE mmobj_ssechar(16, 1, 32);
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
