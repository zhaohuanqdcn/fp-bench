// This program computes a prefix sum over an array of floating-point
// numbers, and asserts that (a) the prefix sum result is
// monotonically increasing, and (b) each element of the prefix sum
// result is larger than or equal to the corresponding element of the
// input.  This holds if every element of the input is non-negative.
//


#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

#define FLOAT_TYPE float


#define FLOAT_LITERAL(X) (FLOAT_TYPE)X

void prefix_sum(FLOAT_TYPE data_in[N], FLOAT_TYPE data_out[N]) {
  data_out[0] = data_in[0];
  for(int i = 1; i < N; i++) {
    data_out[i] = data_in[i] + data_out[i-1];
  }
}

int main(int argc, char** argv) {

  FLOAT_TYPE data_in[N];
  FLOAT_TYPE data_out[N];
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
      perror("Error opening file");
      return 1;
  }

  for (int i = 0; i < N; i++) {
    fscanf(file, "%f", &data_in[i]);
  }
  fclose(file);

  for(int i = 1; i < N; i++) {
    if(isnan(data_in[i]) || data_in[i] < FLOAT_LITERAL(0.0)) {
      return 0;
    }
  }

  prefix_sum(data_in, data_out);

  for(int i = 0; i < N; i++) {
    if (data_out[i] < data_in[i]) {
      printf("BUG triggered\n");
      return 1;
    }
    if(i > 0) {
      assert(data_out[i] >= data_out[i-1]);
    }
  }

  return 0;

}
