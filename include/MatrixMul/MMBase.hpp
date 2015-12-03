#ifndef MMBASE_HEADER
#define MMBASE_HEADER

#include <string>
#include <chrono> // for high resolution clock from STD C++
#include <cstdio>
#include <cstdint>
#include <limits.h>

using namespace std;
using namespace std::chrono;

#define HI 1024
#define LO 0
#define MMTIMES 4096

template < class TYPE_T>
class MMBase {
private:
  string _name;
  TYPE_T* mat_A;
  TYPE_T* mat_B;
  TYPE_T* mat_C;
  int D_M;
  int D_N;
  int D_K;
  virtual void mm ( TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K) = 0;
  string Name() {
    return this->_name;
  }
  void initRandomArray(TYPE_T* arr, int size) {
    int i = 0;
    for (; i < size; i++) {
      TYPE_T r3 = LO + static_cast <TYPE_T> (rand()) /( static_cast <TYPE_T> (RAND_MAX/(HI-LO)));
      arr[i] = r3;
    }
  }

public:
  MMBase(int M, int N, int K, string name) {
    this->mat_A = new TYPE_T[M*K];
    this->mat_B = new TYPE_T[K*N];
    this->mat_C = new TYPE_T[M*N];
    this->D_M = M;
    this->D_N = N;
    this->D_K = K;
    this->_name = name;
    initRandomArray(this->mat_A, M*K);
    initRandomArray(this->mat_B, K*N);
    //initRandomArray(this->mat_C, M*K);
    printf("MM A[%dx%d] * B[%dx%d] = C[%dx%d]\n",  M, K, K, N, M, N);
  }
  void runWithTimer() {
    runWithTimer(this->mat_A, this->mat_B, this->mat_C,
      this->D_M, this->D_N, this->D_K);
  }
  void mmWrapper(TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K) {
    int i = 0;
    for (; i < MMTIMES; i++) {
      this->mm(matA, matB, matC, M, N, K);
    }
  }
  void runWithTimer(TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K) {
      using std::chrono::duration_cast;
      using std::chrono::nanoseconds;
      typedef std::chrono::high_resolution_clock clock;
      printf("Warmup\n");
      this->mmWrapper(matA, matB, matC, M, N, K);
      printf("Start Timer\n");
      high_resolution_clock::time_point t1 = clock::now();
      this->mmWrapper(matA, matB, matC, M, N, K);
      high_resolution_clock::time_point t2 = clock::now();
      printf("End Timer\n");
      auto duration = duration_cast<microseconds>(t2 - t1).count();
      float gflops = (2.0 * MMTIMES * this->D_M * this->D_N * this->D_K)/((float)duration*1000);
      cout << this->Name() << " GOPS:" << gflops << endl;
  }
};
#endif //MMBASE_HEADER
