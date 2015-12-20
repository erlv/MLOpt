#include <cassert>
#include <arm_neon.h>
#include "MatrixMul/MMNeon.hpp"


inline __attribute__((always_inline)) static int8_t radd_neon_int8x16(int8x16_t v)  {
   int8_t res=0;
#if defined(__aarch64__)
   // AArch64 new intrinsics
   res = vaddvq_s8(v);
#else
   int64x2_t res_2 = vpaddlq_s32(vpaddlq_s16(vpaddlq_s8(v)));
   res = (int8_t)vadd_s64(vget_high_s64(res_2), vget_low_s64(res_2));
#endif
   return res;

}

void MMInt8Neon::mm(int8_t *__restrict__ matA, int8_t *__restrict__ matB, 
    int8_t *__restrict__ matC, int M, int N, int K) {
#if DETAIL_PRINT
  cout << "Run MM for " << this->Name() << endl;
#endif
  if (N != 1 && K != 1) {
    assert(K%16 == 0); //Due to alignment requirement, K need to satisfy this
    MatrixTrans(matB, K, N);
  }
  int i,j,k;
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      int8x16_t v_res_16 = vdupq_n_s8(0);
      for (k=0; k < K; k+=16) {
        int8x16_t v_A_16 =  vld1q_s8(&matA[i*K + k]);
        int8x16_t v_B_16 =  vld1q_s8(&matB[j*N + k]);
        v_res_16 = vmlaq_s8(v_res_16, v_A_16, v_B_16);
      }
      matC[i*N + j] = radd_neon_int8x16(v_res_16);
    }
  }
#if DETAIL_PRINT
    this->printArray(matC, M, N);
#endif

}
