// Performs the summation of array data in to ways:
//    ((((0 + data[0]) + data[1]) + data[2]) + ... )
//    (0 + (data[0] + (data[1] + (data[2] + ... ))))
// and checks that they are equivalent.  In general they
// need not be, since floating-point addition is not
// associative.
//

#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "klee/klee.h"

#define N 5

#define FLOAT_TYPE float

#define FLOAT_LITERAL(X) (FLOAT_TYPE)X

FLOAT_TYPE sum1(FLOAT_TYPE data[N]) {
  FLOAT_TYPE sum = (FLOAT_TYPE)0;
  for(int i = 0; i < N; i++) {
    sum = sum + data[i];
  }
  return sum;
}

FLOAT_TYPE sum2(FLOAT_TYPE data[N]) {
  FLOAT_TYPE sum = (FLOAT_TYPE)0;
  for(int i = N-1; i >= 0; i--) {
    sum = data[i] + sum;
  }
  return sum;
}


int main(int argc, char** argv) {

  FLOAT_TYPE data[N];
  
  klee_make_symbolic(data, sizeof(FLOAT_TYPE)*N, "data");

  FLOAT_TYPE result1 = sum1(data);
  FLOAT_TYPE result2 = sum2(data);

  if (!((isnan(result1) && isnan(result2)) || (result1 == result2))) {
    printf("BUG triggered\n");
    return 1;
  }

  return 0;

}
