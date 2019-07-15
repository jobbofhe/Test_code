

#include <stdio.h>
#include <stdlib.h>

int func(float **pre)
{
    float *H = (float*)malloc(100);

    pre = &H;
    *pre = H;

    printf("-----1 [%p]\n", pre);
    printf("-----2 [%p]\n", *pre);

    return 0;
}


int main(int argc, char const *argv[])
{
    float *p;

    int ret = func(&p);

    printf("-----3 [%p]\n", p);
    printf("-----4 [%p]\n", *p);



    return 0;
}