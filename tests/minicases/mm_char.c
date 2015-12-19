/*
 * -print-after-all: dump IR after each pass in LLVM
 *
 */
#define SN 9000
signed char matA[SN];
signed char matB[SN];
signed char matC[SN];
void mm (int M, int N, int K) {

  int i,j,k;
  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++) {
      signed char res = 0;
      for (k=0; k < K; k++) {
        res += matA[i*K + k] * matB[k*N + j];
      }
      matC[i*N + j] = res;
    }
  }
}
