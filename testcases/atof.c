#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{
	if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
	char input[8];
	strncpy(input, argv[1], sizeof(input) - 1);
	input[0] = '0';
	input[1] = '.';
	input[sizeof(input) - 1] = 0;
	bool has_e = false;
	for(size_t i = 2; i < sizeof(input) - 1; ++i) {
		if(input[i] == 'e' || input[i] == 'E') has_e = true;
	}
	double out = atof(input);
	assert(out >= 0);
	assert(has_e || out < 1);
	printf("%lf\n", out);
}
