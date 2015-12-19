#ifndef MMSSE_HEADER
#define MMSSE_HEADER

#include <iostream>
#include <string>
#include <cstdint>
#include "MMBase.hpp"

using namespace std;

class MMInt8SSE: public MMBase<int8_t> {
private:
  void MatrixTrans(int8_t* mat, int M, int N);
public:
  MMInt8SSE (int M, int N, int K)
    :MMBase<int8_t>(M,N,K, "MMInt8SSE") {
  }
  void mm(int8_t *__restrict__ matA, int8_t *__restrict__ matB, int8_t *__restrict__ matC, int M, int N, int K) override;
  void verifyResult();
  virtual void initRandomArray(int8_t* arr, int size) override;
};

#endif //MMSSE_HEADER
