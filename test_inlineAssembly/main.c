#include <stdio.h>
#include <stdlib.h>

int main(int argc, char argv[])
{
	int in = 100;
	int out;

	asm volatile(
		"vpcmpeqb   %%ymm5,%%ymm5,%%ymm5  \n"	
		:
		:
		:
	);

	printf("out =%d\n", out);


	int a = 0;

    __asm__ __volatile__(
    	"mov %%ebp, %0 \r\n"
    	"mov %%eax, $1 \r\n"
        :"=m"(a)
        ::"memory"
    );

    printf("--- [%d]\n", a);

	return 0;
}

