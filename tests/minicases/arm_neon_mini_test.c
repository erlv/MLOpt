#include <arm_neon.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define N  256
#define MAX 6
int16_t A[N];
int16_t B[N];
int16_t C_1[N];
int16_t C_2[N];

void add_c() {
  int i=0;
  for (; i < N; i++) {
    C_1[i] = A[i] + B[i];
  }
}

void add_neon_c() {
  int i=0;
  for (; i < N; i +=8) {
    int16x8_t v_a = vld1q_s16(&A[i]);
    int16x8_t v_b = vld1q_s16(&B[i]);
    int16x8_t v_c = vaddq_s16(v_a, v_b);
    vst1q_s16(&C_2[i], v_c);
  }
}


bool compare_arr() {
  int i=0;
  for(; i < N; i++) {
    if (C_1[i] != C_2[i]) {
      printf("%d: %d != %d\n", i, C_1[i], C_2[i]);
      return false;
    }
  }
  return true;
}

int main() {
  int i=0;
  srand(0);
  for (; i< N; i++) {
    A[i] = rand()/MAX;
    B[i] = rand()/MAX;
    C_1[i] = rand()/MAX;
    C_2[i] = rand()/MAX;
  }
  add_c();
  add_neon_c();
  if(compare_arr()) {
    printf("PASS\n");
  } else {
    printf("FAIL\n");
  }
  return 0;
}
