#ifndef MMNEON_HEADER
#define MMNEON_HEADER

#include <iostream>
#include <string>
#include <cstdint>
#include "MMSSE.hpp"

using namespace std;

class MMInt8Neon: public MMInt8Opt {
public:
  MMInt8Neon (int M, int N, int K)
    :MMInt8Opt(M, N, K) {
      this->_name = "MMInt8Opt_Neon";
  }
  virtual void mm(int8_t *__restrict__ matA, int8_t *__restrict__ matB,
   int8_t *__restrict__ matC, int M, int N, int K) override;
};
#endif //MMNEON_HEADER
