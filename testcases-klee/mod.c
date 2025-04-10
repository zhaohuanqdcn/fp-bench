#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include "klee/klee.h"

static void ftest(float f, float g) {
	assert(fmodf(f, g) == f);
}

static void dtest(double f, double g) {
	assert(fmod(f, g) == f);
}

#define test(f, g) _Generic((f), \
	float: ftest, \
	double: dtest \
	)(f, g)

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	int version;
	double input1, input2;
	
	klee_make_symbolic(&version, sizeof(version), "version");
 	klee_make_symbolic(&input1, sizeof(input1), "input1");
  	klee_make_symbolic(&input2, sizeof(input2), "input2");

	int valid = 1;
	valid &= !isnan(input1);
	valid &= !isinf(input1);
	valid &= (input1 > 0);
	valid &= !isnan(input2);
	valid &= !isinf(input2);
	valid &= (input2 > 0);
	valid &= (input2 > input1);

	if (!valid) {
		return 0;
	}

	if (version == 0) {
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f = (float) input1;
		float g = (float) input2;

		test(f, g);
	}
	else if (version == 1) {
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f = (double) input1;
		double g = (double) input2;
		
		test(f, g);
	}

}
