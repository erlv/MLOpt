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
  return 0;
}

int main() {
  int8SSEVSint8();
  return 0;
}
