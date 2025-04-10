#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "klee/klee.h"

typedef struct struc {
	int a;
	double b;
} struc;

void f(struc*, int, double);

int main(int argc, char** argv) {
	int i;
	double d;

	klee_make_symbolic(&i, sizeof(i), "i");
  	klee_make_symbolic(&d, sizeof(d), "d");

	struc x = {.a = i, .b = d};
	f(&x, i, d);
}

void f(struc* s, int i, double d) {
	assert(s->a == i);
	assert(s->b == d);
}
