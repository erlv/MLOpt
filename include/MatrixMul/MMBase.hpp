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
#define MMTESTTIMES 1
#ifdef MINITEST
#define PRE_D_M 64
#define PRE_D_N 1
#define PRE_D_K 64
#else
#define PRE_D_M 512
#define PRE_D_N 1
#define PRE_D_K 2048
#endif

template < class TYPE_T>
class MMBase {
public:
  bool is_allocated;
  string _name;
  TYPE_T* mat_A;
  TYPE_T* mat_B;
  TYPE_T* mat_C;
  int D_M;
  int D_N;
  int D_K;
  int _MM_Times;
  virtual void mm ( TYPE_T *__restrict__  matA, TYPE_T *__restrict__ matB, TYPE_T *__restrict__ matC, int M, int N, int K) = 0;

  virtual void initRandomArray(TYPE_T* arr, int size) {
    int i = 0;
    for (; i < size; i++) {
      TYPE_T r3 = LO + static_cast <TYPE_T> (rand()) /( static_cast <TYPE_T> (RAND_MAX/(HI-LO)));
      arr[i] = r3;
    }
  }

public:
  string Name() {
    return this->_name;
  }
  void fastMode() {
    this->_MM_Times = MMTESTTIMES;
  }

  MMBase(): _MM_Times(MMTIMES) {}
  MMBase(int M, int N, int K, string name):_MM_Times(MMTIMES) {
    this->mat_A = new TYPE_T[M*K];
    this->mat_B = new TYPE_T[K*N];
    this->mat_C = new TYPE_T[M*N];
    this->D_M = M;
    this->D_N = N;
    this->D_K = K;
    this->_name = name;
    this->is_allocated = true;
    srand(0);
    printf("MM A[%dx%d] * B[%dx%d] = C[%dx%d]\n",  M, K, K, N, M, N);
  }
  ~MMBase() {
    if (this->is_allocated) {
      delete[] this->mat_A;
      delete[] this->mat_B;
      delete[] this->mat_C;
    }
  }
  void initArray() {
    initRandomArray(this->mat_A, this->D_M * this->D_K);
    initRandomArray(this->mat_B, this->D_K * this->D_N);

#if DETAIL_PRINT
    cout << "Print Mat_A" << endl;
    printArray(this->mat_A, this->D_M, this->D_K);
    cout << "Print Mat_B" << endl;
    printArray(this->mat_B, this->D_K, this->D_N);
#endif

  }
  void printArray(TYPE_T* mat, int M, int N) {
    int i,j;
    for (i=0; i < N; i++) {
      for (j=0; j < M; j++) {
        cout << (int)mat[i*N + j];
        if (j < (M-1)) {
          cout << "\t";
        }
      }
      cout << endl;
    }
  }

  void runWithTimer() {
    runWithTimer(this->mat_A, this->mat_B, this->mat_C,
      this->D_M, this->D_N, this->D_K);
  }
  void mmWrapper(TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K) {
    int i = 0;
    for (; i < this->_MM_Times; i++) {
      this->mm(matA, matB, matC, M, N, K);
    }
  }
  void runWithTimer(TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K) {
      using std::chrono::duration_cast;
      using std::chrono::nanoseconds;
      typedef std::chrono::high_resolution_clock clock;
      printf("Warmup...........");
      this->mmWrapper(matA, matB, matC, M, N, K);
      printf("Start Timer.............");
      high_resolution_clock::time_point t1 = clock::now();
      this->mmWrapper(matA, matB, matC, M, N, K);
      high_resolution_clock::time_point t2 = clock::now();
      printf("End Timer\n");
      auto duration = duration_cast<microseconds>(t2 - t1).count();
      float gflops = (2.0 * MMTIMES * this->D_M * this->D_N * this->D_K)/((float)duration*1000);
      cout << this->Name() << " GOPS:" << gflops << endl;
  }
  void runOnce() {
    this->mm(this->mat_A, this->mat_B, this->mat_C, this->D_M, this->D_N, this->D_K);
  }
  bool compareRes(TYPE_T* matC) {
    int i = 0 ;
    for (; i < (this->D_M * this->D_N); i++) {
      if (matC[i] != this->mat_C[i]) {
        cout << i << ":" <<  std::hex << (int)matC[i] << "!="
             << (int)this->mat_C[i] << std::dec << endl;
        return false;
      } else {
#if DETAIL_PRINT
        cout << i << ":"<< std::hex << (int)matC[i] << "=="
             << (int)this->mat_C[i] << std::dec << endl;
#endif // DETAIL_PRINT
      }
    }
    if (i == this->D_M * this->D_N) {
      return true;
    } else {
      return false;
    }
  }
};
#endif //MMBASE_HEADER
