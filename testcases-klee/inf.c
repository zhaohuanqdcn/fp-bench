#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "klee/klee.h"

static void finftest(float f) {
	//printf("%f (expected inf)\n", f);
	assert(f == f);
	assert(f > 0);
	assert(f > FLT_MAX);
	assert(f == INFINITY);
	assert(f - f != f - f);
}

static void dinftest(double f) {
	//printf("%lf (expected inf)\n", f);
	assert(f == f);
	assert(f > 0);
	assert(f > DBL_MAX);
	assert(f == INFINITY);
	assert(f - f != f - f);
}

#define inftest(f) _Generic((f), \
	float: finftest, \
	double: dinftest \
	)(f)

static void finftest_n(float f) {
	//printf("%f (expected inf)\n", f);
	assert(f == f);
	assert(f < 0);
	assert(f < -FLT_MAX);
	assert(f == -INFINITY);
	assert(f - f != f - f);
}

static void dinftest_n(double f) {
	//printf("%lf (expected inf)\n", f);
	assert(f == f);
	assert(f < 0);
	assert(f < -DBL_MAX);
	assert(f == -INFINITY);
	assert(f - f != f - f);
}

#define inftest_n(f) _Generic((f), \
	float: finftest_n, \
	double: dinftest_n \
	)(f)

static void ftest(float f) {
	inftest(f);
	inftest_n(-f);

	f = f + 1;
	inftest(f);

	f -= FLT_MAX;
	inftest(f);
}

static void dtest(double f) {
	inftest(f);
	inftest_n(-f);

	f = f + 1;
	inftest(f);

	f -= DBL_MAX;
	inftest(f);
}


#define test(f) _Generic((f), \
	float: ftest, \
	double: dtest \
	)(f)

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	int version;
	double input;
	klee_make_symbolic(&version, sizeof(version), "version");
  	klee_make_symbolic(&input, sizeof(input), "input");

	if (version == 0) {
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f = INFINITY;
		test(f);

		f = (float) input;

		if (isnan(f)) {
			return 0;
		}

		f = fabsf(f) + 3.1415926535e10;
		for(unsigned i = 0; i < 2; ++i) {
			f = f*f;
		}
		test(f);
	}
	else if (version == 1) {
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f = INFINITY;
		test(f);

		f = (double) input;

		if (isnan(f)) {
			return 0
			;
		}
		f = fabs(f) + 3.1415926535e78;
		for(unsigned i = 0; i < 2; ++i) {
			f = f*f;
		}
		test(f);
	}

}
