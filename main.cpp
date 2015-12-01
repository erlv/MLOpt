#include <cstdint>
#include <iostream>
#include "MMScalar.hpp"

using namespace std;


int main() {
  MMScalar<float> mmobj_float(512, 1, 2048, "float");
  mmobj_float.runWithTimer();
  MMScalar<int8_t> mmobj_char(512,1, 2048, "int8_t");
  mmobj_char.runWithTimer();
}
