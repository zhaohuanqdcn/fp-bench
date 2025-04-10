#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int i;
	int j;
	if (argc != 3) {
		printf("Usage: %s <int> <int>\n", argv[0]);
		return 1;
	}

	i = atoi(argv[1]);
	j = atoi(argv[2]);
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
