#ifndef MMSSE_HEADER
#define MMSSE_HEADER

#include <iostream>
#include <string>
#include <cstdint>
#include "MMInt8Opt.hpp"

using namespace std;

class MMInt8SSE: public MMInt8Opt {
public:
  MMInt8SSE (int M, int N, int K)
    :MMInt8Opt(M, N, K) {
      this->_name = "MMInt8Opt_SSE";
  }
  void mm(int8_t *__restrict__ matA, int8_t *__restrict__ matB, int8_t *__restrict__ matC, int M, int N, int K) override;

};

#endif //MMSSE_HEADER
