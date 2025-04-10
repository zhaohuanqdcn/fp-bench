#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

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
	if (argc != 4) {
		printf("Usage: %s <int> <double> <double>\n", argv[0]);
		return 1;
	}

	version = atoi(argv[1]);
	input1 = atof(argv[2]);
	input2 = atof(argv[3]);

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
