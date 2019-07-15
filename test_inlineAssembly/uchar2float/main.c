
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if 1

//------------------------------------------------------------------------------
float flt = 3.3123255;


float itof (int in)
{   
    struct  timeval tv1, tv2; 
    int count = 1920*1080;
    int i = 0;
    gettimeofday(&tv1, NULL); 
    for (i; i < count; ++i)
    {
        __asm__ __volatile__(
            ".att_syntax        \n\t"
            "movl %0,  %%eax    \n\t"
            "bt   $31, %%eax    \n\t"
            "jnc  plus          \n\t"
            "movl $flt, %%eax   \n\t"
            "rcr  $1, %%eax     \n\t"
            "neg  %%eax         \n\t"
            "plus:              \n\t"
            "movl $0x7F, %%edx  \n\t"
            "bsr  %%eax, %%ebx  \n\t"
            "movl $23, %%ecx    \n\t"
            "cmp  %%ecx, %%ebx  \n\t"
            "jbe  fit           \n\t"
            "sub  %%cl, %%bl    \n\t"
            "mov  %%bl, %%cl    \n\t"
            "shr  %%cl, %%eax   \n\t"
            "setc %%cl          \n\t"
            "addl %%ecx, %%eax  \n\t"
            "addl %%ebx, %%edx  \n\t"
            "mov  $23, %%cl     \n\t"
            "fit:               \n\t"
            "bsr %%eax , %%ebx  \n\t"
            "btr %%ebx, %%eax   \n\t"
            "sub %%bl, %%cl     \n\t"
            "shl %%cl, %%eax    \n\t"
            "addl %%edx, %%ebx  \n\t"
            "orl  (flt), %%eax  \n\t"
            "shl $23, %%ebx     \n\t"
            "orl (flt), %%ebx   \n\t"
            :
            :"r"(in)
            :"eax", "ebx", "ecx", "edx"
        );
    }
    gettimeofday(&tv2, NULL); 
    float ftime = (1000000 * (tv2.tv_sec - tv1.tv_sec) + tv2.tv_usec- tv1.tv_usec)/1000.0; 
    printf("\n1---------->>>> time [%f] ms.\n", ftime);


    return flt;
}

float uchar2float(unsigned char uchar)
{
    float f = (float)uchar;
    return f;
}
int main (void)
{
    struct  timeval tv1, tv2; 

    float fltf = 2.2;
    int i = 7;
    printf("%d  %f\n", i, fltf);

    fltf = itof(i);
    printf("%d  %f\n", i, fltf);


    int count = 1920*1080;
    unsigned char uchar = 125;

    gettimeofday(&tv1, NULL); 
    for (i = 0; i < count; ++i)
    {
        float ftmp = uchar2float(uchar);
    }
    gettimeofday(&tv2, NULL); 
    float ftime = (1000000 * (tv2.tv_sec - tv1.tv_sec) + tv2.tv_usec- tv1.tv_usec)/1000.0; 
    printf("\n1---------->>>> time [%f] ms.\n", ftime);

    return 0;
}

#endif


//------------------------------------------------------------------------------
/*
int main()
{
    int in = 9;
    __asm__ volatile(
        "xorl %%eax, %%eax   \n"
        "mov $4 (%%esp), %%edx\n"
        "test %%edx, %%edx\n"
        "jz .done\n"
        "jns .pos\n"
        "orl $0x80000000, %%eax\n"  // ; set sign bit
        "negl %%edx\n"
    ".pos:\n"
        "bsrl %%edx, %%ecx\n" //; shift the highest bit set into bit #23
        
        "subl $23, %%ecx\n"
        "rorl %%cl, %%edx\n"         //; works for cl < 0 too
        "andl $0x007fffff, %%edx\n"  //; chop off highest bit
        "orl %%edx, %%eax\n"        //; mantissa
        "addl $150, %%ecx\n"   //; bias
        "shll $23, %%ecx\n"
        "orl %%ecx， %%eax \n"        // ; exponent
    ".done:\n"
    "ret\n"
    :
    :"r"(in)
    );
}
*/


//------------------------------------------------------------------------------
/*
int main()
{
    int a = 10, b = 56, c = 8;
    __asm__ __volatile__(
        "addl %0, %%eax   \n"
        "addl %1, %%eax   \n"
        :"=r"(b)      
        :"r"(a), "r"(c)       
        :"%eax");     
     
    printf("Result: %d, %d\n", a, b);
}
*/




//------------------------------------------------------------------------------
// add
#if 0
int asm_add(int a, int b)
{
    __asm__ __volatile__ (
        ".intel_syntax\n"
        "add %0, %1 \n"
        ".att_syntax \n"
        :"+r"(a)
        :"r"(b)
    );

  return a;
}


int main()
{
    int re = asm_add(100, 1);
    
    printf("re[%d]\n", re);    

    //----------------------------------------------
    // 扩展内联汇编
    int foo = 10;
    int bar = 15;
    __asm__ __volatile__(
        "addl %%ebx, %%eax"
        :"=a"(foo)
        :"a"(foo), "b"(bar)
    );

    printf("foo+bar=%d\n", foo);


    //----------------------------------------------
    // 普通内联汇编
    
    asm(
        "addl $1, g_num \n\t"
        "subl $3, g_num \n\t"
    );

    printf("result is [%d]\n", g_num);
}
#endif


//------------------------------------------------------------------------------
// strcpy
#if 0
/*
    源地址存放于 esi，目标地址存放于 edi，同时开始拷贝，当我们到达 0 时，拷贝完成。
    约束 "&S"、"&D"、"&a" 表明寄存器 esi、edi 和 eax 早期修饰寄存器，也就是说，它
    们的内容在函数完成前会被改变。这里很明显可以知道为什么 "memory" 会放在修饰寄存
    器列表。
 */
static inline char * my_strcpy(char * dest,const char *src)
{
    int d0, d1, d2;
    __asm__ __volatile__(  
        "1:\tlodsb          \n\t"
        "stosb              \n\t"
        "testb %%al,%%al    \n\t"
        "jne 1b"
        : "=&S" (d0), "=&D" (d1), "=&a" (d2)
        : "0" (src),"1" (dest) 
        : "memory"
    );

    return dest;
}

int main()
{
    char *src = "assembly src test";
    char dst[64];

    char *restr = my_strcpy(dst, src);

    printf("restr [%s]\n", restr);
}

#endif


//------------------------------------------------------------------------------
#if 0
#define  NUMBER     10000000


int foo(int x)
{
    int i, y, total;
    total = 0;
    for (i = 0; i < NUMBER; i++) 
    {
        asm volatile(
            "addl %1,%0"
            : "=r" (y)
            : "g" (x)
        );

        total += y;
    }
    return total;
}

int foo_no(int x)
{
    int i, y, total;
    total = 0;
    for (i = 0; i < NUMBER; i++) 
    {
        y = x + i;
        total += y;
    }
    return total;
}


int main()
{
    gettimeofday(&tv1, NULL); 
    int reFoo1 = foo(66);
    gettimeofday(&tv2, NULL); 

    float ftime = (1000000 * (tv2.tv_sec - tv1.tv_sec) + tv2.tv_usec- tv1.tv_usec)/1000.0; 
    printf("\n1---------->>>> time [%f]\n", ftime);

    
    gettimeofday(&tv1, NULL); 
    int reFoo2 = foo_no(66);
    gettimeofday(&tv2, NULL); 

    float ftime2 = (1000000 * (tv2.tv_sec - tv1.tv_sec) + tv2.tv_usec- tv1.tv_usec)/1000.0; 
    printf("\n2---------->>>> time [%f]\n", ftime2);
    

    printf("[%d]\n", reFoo1);
    return 0;
}
#endif



//------------------------------------------------------------------------------








//------------------------------------------------------------------------------
#if 0
void uchar2float(uint8 src, uint8 dst) 
{
    asm volatile (
        "vpcmpeqb   %%ymm5,%%ymm5,%%ymm5            \n"
        ".intel_syntax                              \n"
        "add %0, %1                                 \n"
        ".att_syntax                                \n"
        :"+r"(dst)
        :"r"(src)
        : "memory", "cc", "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5" 
    );

    printf("src, dst [%u %d]\n", src, dst);
}


int main(int argc, char argv[])
{
    int in = 100;
    int out = 0;

    unsigned char number1 = 3, number2 = 5;
    float  fNum = 0.0;

    uchar2float(number1, number2);


    printf("out =%d\n", out);




/*
    //----------------------------------------------
    int a = 10, b;
    asm volatile(
        ""
        "movl %1, %%eax \n"
        "movl %%eax, %0 \n"
        :"=r"(b)
        :"r"(a)
        :"%eax"
        );

    printf("a = %d, b = %d\n", a, b);

*/

    return 0;
}

#endif

//------------------------------------------------------------------------------
#if 0
// Use the shift operation to convert data types

#define SIGN_MASK       (1 << 31)
#define HIDDEN_MASK     (1 << 23)
#define MANTISSA_MASK   (HIDDEN_MASK - 1)

#define INT_MIN 0x80000000
#define INT_MAX 0x7FFFFFFF

float intToFloat(int n)
{
    int sign;
    int exp;
    unsigned int half;

    if (n == 0)
         return 0.0f;

    if (n == INT_MIN)
        return -(float)(INT_MIN);

    sign = n < 0 ? SIGN_MASK : 0;
    if (sign)
        n = -n;

    if (!(n & ~(HIDDEN_MASK | MANTISSA_MASK)))
        for (exp = 0; !(n & HIDDEN_MASK); n <<= 1, exp--) ;
    else
    {
        half = 0;
        for (exp = 0; n & ~(HIDDEN_MASK | MANTISSA_MASK); exp++)
        {
            half >>= 1;
            if (n & 1)
                half |= 0x80000000;
            n >>= 1;
        }
        if (half > INT_MIN || ((half == INT_MIN) && (n & 1) != 0))
        {
            n++;
            if (n == 0x1000000)
            {
                n = 0; // or 0x800000, doesn't matter.
                exp++;
            }
        }

    }

    exp = (exp + 127 + 23) << 23;
    n = (n & MANTISSA_MASK) | sign | exp;

    return *((float *)&n);
}


int main()
{   
    unsigned char unum = 5;
    int n = 10;
    float fnum = 0.0;

    fnum = intToFloat(unum);

    printf("fnum [%f]\n", fnum);


    // const float f = 3.2;
    // unsigned char b[sizeof(float)];
    // memcpy(b, &f, sizeof(f));
    // float newF = 0.0;
    // memcpy(&newF, b, sizeof(float));
    // printf("newF[%f]\n", newF);


}
#endif

//------------------------------------------------------------------------------



