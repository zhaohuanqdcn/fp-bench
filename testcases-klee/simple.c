#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "klee/klee.h"

int main(int argc, char** argv) {
	int i;
	int j;
	klee_make_symbolic(&i, sizeof(i), "i");
	klee_make_symbolic(&j, sizeof(j), "j");
	if (j < 10) {
		return 0;
	}
	
	i = i + j;

	double d = (double) i;

	if(i == 0 && j == 11 && d != 0.3) {
		printf("BUG triggered");
		return 1;
	} else {
		printf("Done");
	}
}
