#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	double d;
	if (argc != 2) {
		printf("Usage: %s <double>\n", argv[0]);
		return 1;
	}

	d = atof(argv[1]);
	if (d != d) {
		return 0;
	}

	// division by 2 is exact
	if(d == 0.5) {
		assert(d == 0.5);
		assert(d / 2 == 0.25);
	} else {
		assert(d != 0.5);
		assert(d / 2 != 0.25);
	}
}
