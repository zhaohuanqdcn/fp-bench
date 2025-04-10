#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	int version;
	double input;
	if (argc != 3) {
		printf("Usage: %s <int> <double>\n", argv[0]);
		return 1;
	}

	version = atoi(argv[1]);
	input = atof(argv[2]);

	if (input != input) {
		return 0;
	}

	if (version == 0) {
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f = (float) input;
		float a = fabsf(f);
		float b = sqrtf(f*f);
		if (!(b == INFINITY || b == 0 || (a * 0.99 <= b && a >= b * 0.99))) {
			printf("BUG triggered");
			return 1;
		}
		if (!(a * 0.99 <= b && a >= b * 0.99)) {
			printf("BUG triggered");
			return 1;
		}
		if (!(a == b)) {
			printf("BUG triggered");
			return 1;
		}
	}
	else if (version == 1) {
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f = (double) input;
		double a = fabs(f);
		double b = sqrt(f*f);
		if (!(b == INFINITY || b == 0 || (a * 0.99 <= b && a >= b * 0.99))) {
			printf("BUG triggered");
			return 1;
		}
		if (!(a * 0.99 <= b && a >= b * 0.99)) {
			printf("BUG triggered");
			return 1;
		}
		if (!(a == b)) {
			printf("BUG triggered");
			return 1;
		}
	}
}
