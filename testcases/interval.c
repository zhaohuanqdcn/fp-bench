// Performs an additive computation using double-precision arithmetic
// and single-precision interval arithmetic, and asserts that the
// double-precision result is contained in the single-precision
// interval.

// This program sets the rounding mode and so must set this pragma to tell the
// compiler we will be using/modifying the floating point environment.
// Otherwise the program would be undefined (See 7.6.1 The FENV_ACCESS pragama
// - C11 specification).
#pragma STDC FENV_ACCESS ON
#include <assert.h>
#include <fenv.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N 7

// A single-precision interval
typedef struct interval_s {
  float lower;
  float upper;
} interval_t;

// Neither component of an interval should be NaN, and lower and upper should be ordered.
bool well_formed_interval(interval_t a) {
  return !isnan(a.lower) && !isnan(a.upper) && a.lower <= a.upper;
}

interval_t add_intervals(interval_t a, interval_t b) {
  assert(well_formed_interval(a));
  assert(well_formed_interval(b));
  int old_mode = fegetround(); // Save the rounding mode
  fesetround(FE_DOWNWARD); // Set to round down, to compute lower bound for interval
  float lower = a.lower + b.lower;
  float upper = a.upper + b.upper;
  fesetround(old_mode); // Restore the original rounding mode
  interval_t result = { lower, upper }; // The result is the interval comprised of the computed lower bound and the computed upper bound
  return result;
}

// Determines whether the given double-precision number is inside the single-precision interval.
bool in_interval(double x, interval_t a) {
  assert(!isnan(x));
  assert(well_formed_interval(a));
  return x >= (double)a.lower && x <= (double)a.upper;
}

int main(int argc, char** argv) {

  // The program adds 'increment' to 'initial' N times.
  float initial;
  float increment;

  // The addition is performed relatively precisely, using a double,
  // as well as imprecisely, using a single-precision interval
  double precise;
  interval_t imprecise;
  
  if (argc != 3) {
    printf("Usage: %s <float1> <float2>\n", argv[0]);
    return 1;
  }
  initial = atof(argv[1]);
  increment = atof(argv[2]);

  // We are not interested in NaNs for this benchmark
  if(isnan(initial) || isnan(increment)) {
    return 0;
  }

  // Avoid infinities otherwise we'll eventually we
  // might do  "inf + inf" which will give NaN.
  if (isinf(initial) || isinf(increment)) {
    return 0;
  }

  // Initialise the double and the interval
  precise = (double)initial;
  imprecise.lower = initial;
  imprecise.upper = initial;
  assert(well_formed_interval(imprecise));

  // Do the arithmetic and tests
  for(int i = 0; i < N; i++) {
    if (!in_interval(precise, imprecise)) {
      printf("BUG triggered!");
      return 1;
    }
    precise += (double)increment;
    interval_t increment_interval = { increment, increment };
    imprecise = add_intervals(imprecise, increment_interval);
  }
  if (!in_interval(precise, imprecise)) {
    printf("BUG triggered!");
    return 1;
  }
  return 0;

}
