// This program sets the rounding mode and so must set this pragma to tell the
// compiler we will be using/modifying the floating point environment.
// Otherwise the program would be undefined (See 7.6.1 The FENV_ACCESS pragama
// - C11 specification).
#pragma STDC FENV_ACCESS ON

#include <assert.h>
#include <fenv.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> // For memcpy()
#include "klee/klee.h"

typedef struct {
  double rne;
  double ru;
  double rd;
  double rz;
} Result;

void setRoundingMode(int rm) {
  int result = fesetround(rm);
  assert(result == 0);
  int newRoundingMode = fegetround();
  assert(newRoundingMode != -1);
  assert(newRoundingMode == rm);
}

int isNaNOrInf(double d) {
  return isnan(d) | isinf(d);
}

double toDouble(uint64_t data) {
  assert(sizeof(uint64_t) == sizeof(double));
  double initialValue = 0.0;
  memcpy(&initialValue, &data, sizeof(double));
  return initialValue;
}

uint64_t toBitsFromDouble(double d) {
  assert(sizeof(uint64_t) == sizeof(double));
  uint64_t toReturn;
  memcpy(&toReturn, &d, sizeof(double));
  return toReturn;
}

void printFloat(const char* lead, double d) {
  printf("%s: %.40e (hexfloat: %a) (bits: 0x%" PRIx64 ")\n", lead, d, d, toBitsFromDouble(d));
  fflush(stdout);
}

// This is a hack to prevent clang from optimizing
// the calls to sqrt() such that the rounding mode has
// no effect.
__attribute__((noinline)) double callSqrt(double d) {
  double temp = sqrt(d);
  return temp;
}

int main(int argc, char **argv) {
  // This value should trigger the bug and was found using
  // LibFuzzer.
  double initialValue;
  if (argc != 2) {
    printf("Usage: %s <float>\n", argv[0]);
    return 1;
  }
  initialValue = atof(argv[1]);
  printFloat("Initial Value", initialValue);

  if (isnan(initialValue) || isinf(initialValue)) {
    // Not interesting here
    return 0;
  }

  Result r;
  setRoundingMode(FE_TONEAREST);
  r.rne = callSqrt(initialValue);
  setRoundingMode(FE_UPWARD);
  r.ru = callSqrt(initialValue);
  setRoundingMode(FE_DOWNWARD);
  r.rd = callSqrt(initialValue);
  setRoundingMode(FE_TOWARDZERO);
  r.rz = callSqrt(initialValue);

  printFloat("Result RNE", r.rne);
  printFloat("Result RU ", r.ru);
  printFloat("Result RD ", r.rd);
  printFloat("Result RZ ", r.rz);

  setRoundingMode(FE_TONEAREST);

  // sqrt() of -ve number should give a NaN
  if (initialValue < 0.0) {
    assert(isnan(r.rne));
    assert(isnan(r.ru));
    assert(isnan(r.rd));
    assert(isnan(r.rz));
    return 0;
  }

  assert(!isNaNOrInf(r.rne));
  assert(!isNaNOrInf(r.ru));
  assert(!isNaNOrInf(r.rd));
  assert(!isNaNOrInf(r.rz));


  // sqrt() should not return a negative value so this should
  // always hold.
  assert(r.rd == r.rz);
  assert(r.ru > r.rd);

  if (r.rne != r.ru) {
    printf("BUG triggered!\n");
  }
  return 0;
}
