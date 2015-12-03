#ifndef MMSCALAR_HEADER
#define MMSCALAR_HEADER

#include <iostream>
#include <string>
#include "MMBase.hpp"

using namespace std;

// MM of matA, matB result in matC.
// matA: M X K
// matB: K X N
// matC: M X N
template < class TYPE_T>
class MMScalar: public MMBase<TYPE_T> {
public:
  MMScalar(int M, int N, int K, string postfix)
    : MMBase<TYPE_T>(M, N, K, "MMScalar<"+postfix +">")  {
  }
  void mm ( TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K) override {
#if DETAIL_PRINT
    cout << "Run MM for " << this->Name() << endl;
#endif
    int i,j,k;
    for (i = 0; i < M; i++) {
      for (j = 0; j < N; j++) {
        TYPE_T res = 0;
        for (k=0; k < K; k++) {
          res += matA[i*K + k] * matB[k*N + j];
#if DETAIL_PRINT
          printf("matA[%d]=", i*K+k);
          cout << matA[i*K + k];
          printf(", matB[%d]=", k*N+j);
          cout << matB[k*N+j] << endl;
#endif
        }
#if DETAIL_PRINT
        cout << "res=" << res << endl;
#endif
        matC[i*N + j] = res;
      }
    }
  }
};
#endif //MMSCALAR_HEADER
