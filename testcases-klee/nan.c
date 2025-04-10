#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "klee/klee.h"

static void fnantest(float f) {
	//printf("%f (expected nan)\n", f);
	assert(f != f);
	assert(!(f == f));
	assert(!(f < f));
	assert(!(f <= f));
	assert(!(f > f));
	assert(!(f >= f));
}

static void dnantest(double f) {
	//printf("%lf (expected nan)\n", f);
	assert(f != f);
	assert(!(f == f));
	assert(!(f < f));
	assert(!(f <= f));
	assert(!(f > f));
	assert(!(f >= f));
}

#define nantest(f) _Generic((f), \
	float: fnantest, \
	double: dnantest \
	)(f)

#ifdef USE_KLEE
#include <klee/klee.h>
#endif

static void ftest(float f) {
	nantest(f);

	f = f + 1;
	nantest(f);

	f -= f;
	nantest(f);

	f *= 0;
	nantest(f);

	f /= 0;
	nantest(f);

	f = 0;
	f /= 0;
	nantest(f);

	f = INFINITY;
	f -= INFINITY;
	nantest(f);
}

static void dtest(double f) {
	nantest(f);

	f = f + 1;
	nantest(f);

	f -= f;
	nantest(f);

	f *= 0;
	nantest(f);

	f /= 0;
	nantest(f);

	f = 0;
	f /= 0;
	nantest(f);

	f = INFINITY;
	f -= INFINITY;
	nantest(f);
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

	if (input >= 0) {
		return 0;
	}

	if (version == 0) {
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f = (float) input;

		f = sqrtf(f);
		test(f);
	}
	else if (version == 1) {
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f = (double) input;

		f = sqrtf(f);
		test(f);
	}

}
