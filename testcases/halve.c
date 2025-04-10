#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	{
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f, g;
		if (argc != 2) {
			printf("Usage: %s <float>\n", argv[0]);
			return 1;
		}
		f = atof(argv[1]);
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
