#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "klee/klee.h"

#define FLOAT_WIDTH 32
#define FLOAT_TYPE float
#define FLOAT_ZERO 0.0f
#define FLOAT_SQRT_FUNC sqrtf

int main(int argc, char **argv) {
  FLOAT_TYPE x;

  klee_make_symbolic(&x, sizeof(FLOAT_TYPE), "x");

  FLOAT_TYPE result = FLOAT_SQRT_FUNC(x);

  if (isnan(x)) {
    assert(isnan(result));
    return 0;
  }

  if (x < FLOAT_ZERO) {
    assert(isnan(result));
    return 0;
  }

  if (isinf(x)) {
    assert(isinf(result) == 1);
    return 0;
  }

  if (x == FLOAT_ZERO) {
    assert(result == FLOAT_ZERO);
    // check sign bit sqrt(-0.0) == -0.0
    if (signbit(x)) {
      assert(signbit(result));
    }
    return 0;
  }

  assert(x > FLOAT_ZERO);
  return 0;
}
