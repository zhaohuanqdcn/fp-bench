// This example counts the number of single-precision floating-point
// numbers between two bounding single-precision floating-point
// numbers.  The bounding numbers are required to be sufficiently
// close that we know an upper bound on the count.  The benchmark
// checks that the count does not exceed this bound.

#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "klee/klee.h"

#define START_FLOAT 1.0f
#define END_FLOAT 1.00001f
#define FLOATS_BETWEEN_BUG 20
#define FLOATS_BETWEEN_MAX 84

int main(int argc, char** argv) {

  // The program counts all floats between start (inclusive) and end
  // (exclusive)
  float start;
  float end;

  klee_make_symbolic(&start, sizeof(float), "start");
  klee_make_symbolic(&end, sizeof(float), "end");

  // We constrain the bounds to be numbers, ordered, and within the
  // range [START_FLOAT, END_FLOAT].  As a result, FLOATS_BETWEEN
  // gives a bound on the number of single-precision floating-point
  // numbers that lie in between these bounds.

  if(isnan(start) || isnan(end)) {
    return 0;
  }

  if(start > end) {
    return 0;
  }
 
  if(start < START_FLOAT) {
    return 0;
  }

  if(end > END_FLOAT) {
    return 0;
  }

  int count = 0;
  
  // We require that unsigned and float have the same size for the
  // program to operate correctly
  assert(sizeof(unsigned) == sizeof(float));

  // Iterate through the floating-point numbers in the range by
  // bit-conversion to unsigned.
  for(float current = start; current != end; count++) {
    unsigned temp;
    memcpy(&temp, &current, sizeof(float));
    temp++;
    memcpy(&current, &temp, sizeof(float));
  }

  // Check that the count is non-negative and bounded above by
  // FLOATS_BETWEEN
  printf("Count is %d\n", count);
  assert(count >= 0);
  assert(FLOATS_BETWEEN_MAX);
  if (count <= FLOATS_BETWEEN_BUG) {
    printf("BUG triggered!");
    return 1;
  }
  return 0;
}
