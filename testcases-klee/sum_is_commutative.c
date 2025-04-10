// Performs the summation of array data in to ways:
//    ((((0 + data[0]) + data[1]) + data[2]) + ... )
//    ( ... + (data[2] + (data[1] + (data[0] + 0))))
// and checks that they are equivalent.  They should be,
// since floating-point addition is commutative.
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
  FLOAT_TYPE sum = (FLOAT_TYPE)0.0f;
  for(int i = 0; i < N; i++) {
    sum = sum + data[i];
  }
  return sum;
}

FLOAT_TYPE sum2(FLOAT_TYPE data[N]) {
  FLOAT_TYPE sum = (FLOAT_TYPE)0.0f;

// This is kind of clumsy but it
// is here to work around a bug clang 3.4
// where the debug information on `data[i]`
// is wrong when it is inside the loop head
// which is split accross multiple lines.
#define LOOP_BOUND(i) data[i]
  for(int i = 0; i < LOOP_BOUND(i) ; ++i) {
    sum = data[i] + sum;
  }
  return sum;
#undef LOOP_BOUND
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
