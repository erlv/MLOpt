#include <cassert>
#include <x86intrin.h>
#include "MatrixMul/MMSSE.hpp"

inline __attribute__((always_inline)) static int8_t radd_sse_int16x8(__m128i v)  {
        __m128i v_lo_4 = _mm_cvtepi16_epi32(v);
        __m128i v_hi_4 = _mm_cvtepi16_epi32(_mm_shuffle_epi32(v, 0x4e));
        __m128i v_int_4 = _mm_add_epi32(v_lo_4, v_hi_4); //sum in the  4x32b
        v_hi_4 = _mm_shuffle_epi32(v_int_4, 0x4e);
        v_int_4 = _mm_add_epi32(v_int_4, v_hi_4); // sum in the lower 2x32b of v_2
        v_hi_4 = _mm_shuffle_epi32(v_int_4, 0xe1);
        v_int_4 = _mm_add_epi32(v_int_4, v_hi_4); // sum in the lower 1x32b of v_2
        int8_t res = (int8_t)_mm_extract_epi32(v_int_4, 0);
        return res;
}


void MMInt8SSE::mm(int8_t *__restrict__ matA, int8_t *__restrict__ matB, int8_t *__restrict__ matC, int M,
    int N, int K) {
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
      __m128i v_res_8 = _mm_setzero_si128();
      for (k=0; k < K; k+=16) {
        __m128i v_A_16 = _mm_load_si128((__m128i *)&matA[i*K + k]);
        __m128i v_B_16 = _mm_load_si128((__m128i *)&matB[j*N + k]);
        __m128i v_1_8 = _mm_maddubs_epi16(v_A_16, v_B_16);
        v_res_8 = _mm_add_epi16(v_res_8, v_1_8);
      }
      matC[i*N + j] = radd_sse_int16x8(v_res_8);
    }
  }
}
