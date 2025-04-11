#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include "klee/klee.h"

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	{
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f, g;
		klee_make_symbolic(&f, sizeof(f), "f");
		g = f / 2;
		g *= 2;
		if(fabsf(f) < 2*FLT_MIN) {
			assert(fabsf(g) <= 2*FLT_MIN);
			return 0;
		}
		if (f != g) {
			printf("BUG triggered\n");
			return 1;
		}
	}

	return 0;
}
