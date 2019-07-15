#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char str[] = "shuqiang.jpg.f";

    char delims[] = ".";

    char *result = NULL;

    result = strtok( str, delims );
    char name[64];
    printf("%s\n", result);
    
    while( result != NULL ) 
    {
        break;
        result = strtok( NULL, delims );

    }

    printf("%s\n", result);

    return 0;
}