#include <stdio.h>
#include <time.h>
#include <string.h>



char **malloc_for_time()
{   
    // 年/月/日/时/分/秒/星期
    
    char **date = (char**)malloc(sizeof(char*)*7);

    int i = 0;
    for (i = 0; i < 7; ++i)
    {
        date[i] = (char*)malloc(sizeof(char)*32);
    }

    return date;
}

void free_time(char **pTate)
{
    if (!pTate)
    {
        return;
    }
    int i = 0;
    for (i = 0; i < 7; ++i)
    {
        if (pTate[i])
        {
            free(pTate[i]);
            pTate[i] = NULL;
        }
    }
    free(pTate);
    pTate = NULL;
}

void get_local_time(char**date)
{
    char *wday[]={"", "Mon","Tue","Wed","Thu","Fri","Sat", "Sun"};

    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep); /*取得当地时间*/

    // printf ("%d/%d/%d ", (1900+p->tm_year),(1+p->tm_mon), p->tm_mday);
    // printf("%s %d:%d:%d\n", wday[p->tm_wday],p->tm_hour, p->tm_min, p->tm_sec);

    sprintf(date[0], "%d", (1900+p->tm_year));
    sprintf(date[1], "%d", (1+p->tm_mon));
    sprintf(date[2], "%d", (p->tm_mday));
    sprintf(date[3], "%d", (p->tm_hour));
    sprintf(date[4], "%d", (p->tm_min));
    sprintf(date[5], "%d", (p->tm_sec));
    sprintf(date[6], "%s", (wday[p->tm_wday]));
}

int main()
{
    char *wday[]={"", "Mon","Tue","Wed","Thu","Fri","Sat", "Sun"};

    char **date = malloc_for_time();
    get_local_time(date);

    int  i = 0;
    for (i = 0; i < 7; ++i)
    {
        printf("[%s]\n", date[i]);
    }

    free_time(date);

}