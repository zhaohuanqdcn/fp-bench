#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	long double sym, conc;
	if (argc < 2) {
        printf("Usage: %s <ldouble>\n", argv[0]);
        return 1;
    }

	char *endptr;
    sym = strtold(argv[1], &endptr);

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
