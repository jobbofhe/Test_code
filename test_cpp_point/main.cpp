
#include <iostream>

#include <stdio.h>

int func(float **pre)
{
    float *H = new float(3.14);

    pre = &H;
    *pre = H;

    printf("-----0 [%p]\n", H);
    printf("-----1 [%p]\n", pre);
    printf("-----2 [%p]\n", *pre);

    return 0;
}


int main(int argc, char const *argv[])
{   

    float *p = new float;

    int ret = func(p);

    printf("-----3 [%p]\n", p);
    printf("-----4 [%p]\n", p);



    return 0;
}