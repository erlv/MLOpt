#include <cassert>
#include <x86intrin.h>

#include "MatrixMul/MMSSE.hpp"


void MMInt8SSE::MatrixTrans(int8_t* mat, int M, int N) {
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

void MMInt8SSE::mm(int8_t* matA, int8_t* matB, int8_t* matC, int M,
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
        __m128i v_res = _mm_setzero_si128();
        for (k=0; k < K; k+=16) {
          __m128i v_A = _mm_load_si128((__m128i *)&matA[i*K + k]);
          __m128i v_B = _mm_load_si128((__m128i *)&matB[j*N + k]);
          __m128i v_1 = _mm_maddubs_epi16(v_A, v_B);
          v_res = _mm_add_epi16(v_res, v_1);
        }
        __m128i v_lo = _mm_cvtepi16_epi32(v_res);
        __m128i v_hi = _mm_cvtepi16_epi32(_mm_shuffle_epi32(v_res, 0x4e));
        __m128i v_2 = _mm_add_epi32(v_lo, v_hi); //sum in the  4x32b
        v_hi = _mm_shuffle_epi32(v_2, 0x4e);
        v_2 = _mm_add_epi32(v_2, v_hi); // sum in the lower 2x32b of v_2
        v_hi = _mm_shuffle_epi32(v_2, 0xe1);
        v_2 = _mm_add_epi32(v_2, v_hi); // sum in the lower 1x32b of v_2
        matC[i*N + j] = (int8_t)_mm_extract_epi32(v_2, 0);
      }
    }
  }
