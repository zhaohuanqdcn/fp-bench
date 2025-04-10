// This program creates a diagonal matrix where the digonal has values
// 1, 2, 1, 2, ..., and asserts that the matrix has no inverse. 
//

#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FLOAT_TYPE float

#define FLOAT_LITERAL(X) (FLOAT_TYPE)X

#define EPSILON FLT_EPSILON

int N = 4;

// Checks whether two numbers are close to one another
bool very_close(FLOAT_TYPE x, FLOAT_TYPE y) {
  return fabs(x - y) < EPSILON;
}

// Multiplies matrices A and B, putting the result in C
void matrix_mul(FLOAT_TYPE A[N][N], FLOAT_TYPE B[N][N], FLOAT_TYPE C[N][N]) {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      FLOAT_TYPE sum = FLOAT_LITERAL(0.0);
      for(int k = 0; k < N; k++) {
	      sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }
}

// Returns true if and only if matrices A and B multiply to give
// something very close to the identity matrix
bool check_inverses(FLOAT_TYPE A[N][N], FLOAT_TYPE B[N][N]) {
  FLOAT_TYPE C[N][N];
  matrix_mul(A, B, C);
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      if(i == j) {
        if(!very_close(C[i][j], FLOAT_LITERAL(1.0))) {
          return false;
        }
      } else {
        if(!very_close(C[i][j], FLOAT_LITERAL(0.0))) {
          return false;
        }
      }
    }
  }
  return true;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
      perror("Error opening file");
      return 1;
  }

  fscanf(file, "%d", &N);

  FLOAT_TYPE A[N][N];
  FLOAT_TYPE B[N][N];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      fscanf(file, "%f", &B[i][j]);
    }
  }
  fclose(file);

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      if(i == j) {
        if((i % 2) == 0) {
          A[i][j] = FLOAT_LITERAL(1.0);
        } else {
          A[i][j] = FLOAT_LITERAL(2.0);
        }
      } else {
	      A[i][j] = FLOAT_LITERAL(0.0);
      }
    }
  }

  if (!check_inverses(A, B)) {
    printf("BUG triggered!");
    return 1;
  }
  return 0;

}
