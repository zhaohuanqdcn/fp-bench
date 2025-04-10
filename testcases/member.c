#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct struc {
	int a;
	double b;
} struc;

void f(struc*, int, double);

int main(int argc, char** argv) {
	int i;
	double d;

	if (argc != 3) {
		printf("Usage: %s <int> <double>\n", argv[0]);
		return 1;
	}

	i = atoi(argv[1]);
	d = atof(argv[2]);

	struc x = {.a = i, .b = d};
	f(&x, i, d);
}

void f(struc* s, int i, double d) {
	assert(s->a == i);
	assert(s->b == d);
}
