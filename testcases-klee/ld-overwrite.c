#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "klee/klee.h"

int main(int argc, char** argv)
{
	long double sym, conc;
	klee_make_symbolic(&sym, sizeof(sym), "sym");

	char* bits = (char*)&conc;

	for (int i = 15; i >= 0; --i)
	{
		bits[i] = 0xCF;
	}

	conc = sym;

	for (int i = 15; i >= 10; --i)
	{
		assert(bits[i] == (char)0xCF);
	}

	assert(!(sym == sym) || sym == conc);
}
