// Tries to find numbers x and y such that adding y to x N times gives
// successively different results, but adding y an (N+1)th time leaves
// the result unchanged.  We say that the first N additions are not
// absorbed, but the final addition is absorbed.
//

#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3

#define FLOAT_TYPE float

#define FLOAT_LITERAL(X) (FLOAT_TYPE)X

int main(int argc, char** argv) {

  FLOAT_TYPE x;
  FLOAT_TYPE y;

  if (argc != 3) {
    printf("Usage: %s <float1> <float2>\n", argv[0]);
    return 1;
  }
  x = atof(argv[1]);
  y = atof(argv[2]);


  // We are not interested in NaNs for this benchmark
  if(isnan(x) || isnan(y)) {
    return 0;
  }

  // Record the previous value in the summation
  FLOAT_TYPE last = x;
  for(int i = 0; i < N; i++) {
    // Compute the next value in the summation
    FLOAT_TYPE next = last + y;
    // If we have saturated, bail out; this is not interesting for the
    // benchmark
    if(next == last) {
      return 0;
    }
    // Get readyq to move on to nexts summation
    last = next;
  }
  // We want to see whether a final addition of y will be absorbed, so
  // we assert that this will not happen
  if (last + y == last) {
    printf("BUG triggered\n");
    return 1;
  }
  return 0;

}
