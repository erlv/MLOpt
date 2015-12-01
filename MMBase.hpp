#include <string>
#include <chrono> // for high resolution clock from STD C++
#include <cstdio>

using namespace std;
using namespace std::chrono;

template < class TYPE_T>
class MMBase {
private:
  TYPE_T* mat_A;
  TYPE_T* mat_B;
  TYPE_T* mat_C;
  int D_M;
  int D_N;
  int D_K;
  virtual void mm ( TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K) = 0;
  virtual string Name() = 0;

public:
  MMBase(int M, int N, int K) {
    this->mat_A = new TYPE_T[M*K];
    this->mat_B = new TYPE_T[K*N];
    this->mat_C = new TYPE_T[M*N];
    this->D_M = M;
    this->D_N = N;
    this->D_K = K;
    printf("Init MM A[%dx%d] * B[%dx%d] = C[%dx%d]\n",  M, K, K, N, M, N);
  }
  void runWithTimer() {
    runWithTimer(this->mat_A, this->mat_B, this->mat_C,
      this->D_M, this->D_N, this->D_K);
  }
  void runWithTimer(TYPE_T* matA, TYPE_T* matB, TYPE_T* matC, int M, int N, int K) {
      using std::chrono::duration_cast;
      using std::chrono::nanoseconds;
      typedef std::chrono::high_resolution_clock clock;
      high_resolution_clock::time_point t1 = clock::now();
      this->mm(matA, matB, matC, M, N, K);
      high_resolution_clock::time_point t2 = clock::now();
      auto duration = duration_cast<microseconds>(t2 - t1).count();
      cout << this->Name() << ":" << duration << " ms" << endl;
  }
};
