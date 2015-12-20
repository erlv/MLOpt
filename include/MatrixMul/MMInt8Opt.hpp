#ifndef MMINT8OPT_HEADER
#define MMINT8OPT_HEADER

#include <iostream>
#include <string>
#include <cstdint>
#include "MMBase.hpp"
#include "MMScalar.hpp"

using namespace std;

class MMInt8Opt: public MMBase<int8_t> {
public:
  void MatrixTrans(int8_t* mat, int M, int N) {
    for (int i = 0; i<M; i++)
    {
      for (int j = i+1; j<N; j++)
      {
        int8_t temp = *(mat + i*M + j);
        *(mat + i*M + j) = *(mat + j*M + i);
        *(mat + j*M + i) = temp;
      }
    }
  }

  MMInt8Opt (int M, int N, int K)
    :MMBase<int8_t>(M,N,K, "MMInt8Opt") {
  }

  void verifyResult() {
    int8_t* mat_Cseq = new int8_t[this->D_M * this->D_N];
    MMScalar<int8_t> mmobj_verify(this->mat_A, this->mat_B, mat_Cseq, this->D_M,
        this->D_N, this->D_K);
    mmobj_verify.runOnce();
    if (mmobj_verify.compareRes(this->mat_C)) {
      printf("%s verify: PASS\n", this->_name.c_str());
    } else {
      printf("%s verify: FAIL\n", this->_name.c_str());
    }
    delete[] mat_Cseq;
  }

  virtual void initRandomArray(int8_t* arr, int size) override {
    int i = 0;
    for (; i < size; i++) {
      int8_t r3 = LO + static_cast <int8_t> (rand()) % 3;
      arr[i] = r3;
    }
  }
};

#endif //MMINT8OPT_HEADER
