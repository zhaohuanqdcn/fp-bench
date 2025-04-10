#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "klee/klee.h"

int main(int argc, char** argv) {
	long double a, b;
	klee_make_symbolic(&a, sizeof(a), "a");
  	klee_make_symbolic(&b, sizeof(b), "b");

	// the following ensures that no truly annoying cases remain (inf, nan, etc)
	if (a > 1000000 || a < -1000000) {
		return 0;
	}
	if (b > 1000000 || b < -1000000) {
		return 0;
	}

	long double ldsum = a + b;
	double dsum = (double)a + (double)b;
	if (ldsum != dsum) {
		printf("BUG triggered\n");
		return 1;
	}
}
