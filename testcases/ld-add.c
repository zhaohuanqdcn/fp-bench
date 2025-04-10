#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	long double a, b;
	if (argc < 3) {
        printf("Usage: %s <ldouble> <ldouble>\n", argv[0]);
        return 1;
    }

	char *endptr1, *endptr2;
    a = strtold(argv[1], &endptr1);
    b = strtold(argv[2], &endptr2);
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
