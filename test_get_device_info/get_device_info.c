// #include <stdio.h>
// #include <unistd.h>
// #include <sys/time.h>
// #include <string.h>
// #include <stdlib.h>
 
// #define VMRSS_LINE 17
// #define VMSIZE_LINE 13
// #define PROCESS_ITEM 14
 
// typedef struct {
//     unsigned long user;
//     unsigned long nice;
//     unsigned long system;
//     unsigned long idle;
// }Total_Cpu_Occupy_t;
 
 
// typedef struct {
//     unsigned int pid;
//     unsigned long utime;  //user time
//     unsigned long stime;  //kernel time
//     unsigned long cutime; //all user time
//         unsigned long cstime; //all dead time
// }Proc_Cpu_Occupy_t;
 
 
// //获取第N项开始的指针
// const char* get_items(const char*buffer ,unsigned int item){
    
//     const char *p =buffer;
 
//     int len = strlen(buffer);
//     int count = 0;
    
//     int i=0;
//     for (i=0; i<len;i++){
//         if (' ' == *p){
//             count ++;
//             if(count == item -1){
//                 p++;
//                 break;
//             }
//         }
//         p++;
//     }
 
//     return p;
// }
 
 
// //获取总的CPU时间
// unsigned long get_cpu_total_occupy(){
    
//     FILE *fd;
//     char buff[1024]={0};
//     Total_Cpu_Occupy_t t;
 
//     fd =fopen("/proc/stat","r");
//     if (NULL == fd){
//         return 0;
//     }
        
//     fgets(buff,sizeof(buff),fd);
//     char name[64]={0};
//     sscanf(buff,"%s %ld %ld %ld %ld",name,&t.user,&t.nice,&t.system,&t.idle);
//     fclose(fd);
    
//     return (t.user + t.nice + t.system + t.idle);
// }
 
 
// //获取进程的CPU时间
// unsigned long get_cpu_proc_occupy(unsigned int pid){
    
//     char file_name[64]={0};
//     Proc_Cpu_Occupy_t t;
//     FILE *fd;
//     char line_buff[1024]={0};
//     sprintf(file_name,"/proc/%d/stat",pid);
    
//     fd = fopen(file_name,"r");
//     if(NULL == fd){
//         return 0;
//     }
    
//     fgets(line_buff,sizeof(line_buff),fd);
    
//     sscanf(line_buff,"%u",&t.pid);
//     const char *q =get_items(line_buff,PROCESS_ITEM);
//     sscanf(q,"%ld %ld %ld %ld",&t.utime,&t.stime,&t.cutime,&t.cstime);
//     fclose(fd);
    
//     return (t.utime + t.stime + t.cutime + t.cstime);
// }
 
 
// //获取CPU占用率
// float get_proc_cpu(unsigned int pid){
    
//     unsigned long totalcputime1,totalcputime2;
//     unsigned long procputime1,procputime2;
    
//     totalcputime1=get_cpu_total_occupy();
//     procputime1=get_cpu_proc_occupy(pid);
 
//     usleep(200000);
 
//     totalcputime2=get_cpu_total_occupy();
//     procputime2=get_cpu_proc_occupy(pid);
    
//     float pcpu = 0.0;
//     if(0 != totalcputime2-totalcputime1){ 
//         pcpu=100.0 * (procputime2-procputime1)/(totalcputime2-totalcputime1);
//     }
    
//     return pcpu;
// }
 
 
// //获取进程占用内存
// unsigned int get_proc_mem(unsigned int pid){
    
//     char file_name[64]={0};
//     FILE *fd;
//     char line_buff[512]={0};
//     sprintf(file_name,"/proc/%d/status",pid);
    
//     fd =fopen(file_name,"r");
//     if(NULL == fd){
//         return 0;
//     }
    
//     char name[64];
//     int vmrss;
//     int i=0;
//     for (i = 0; i<VMRSS_LINE-1;i++){
//         fgets(line_buff,sizeof(line_buff),fd);
//     }
    
//     fgets(line_buff,sizeof(line_buff),fd);
//     sscanf(line_buff,"%s %d",name,&vmrss);
//     fclose(fd);
 
//     return vmrss;
// }
 
 
// //获取进程占用虚拟内存
// unsigned int get_proc_virtualmem(unsigned int pid){
    
//     char file_name[64]={0};
//     FILE *fd;
//     char line_buff[512]={0};
//     sprintf(file_name,"/proc/%d/status",pid);
    
//     fd =fopen(file_name,"r");
//     if(NULL == fd){
//         return 0;
//     }
    
//     char name[64];
//     int vmsize;
//     int i = 0;
//     for (i=0; i<VMSIZE_LINE-1;i++){
//         fgets(line_buff,sizeof(line_buff),fd);
//     }
    
//     fgets(line_buff,sizeof(line_buff),fd);
//     sscanf(line_buff,"%s %d",name,&vmsize);
//     fclose(fd);
 
//     return vmsize;
// }
 

// // 进程本身
// int get_pid(const char* process_name, const char* user)
// {
//     if(user == NULL){
//         user = getlogin();  
//     }
    
//     char cmd[512];
//     if (user){
//         sprintf(cmd, "pgrep %s -u %s", process_name, user); 
//     }
 
//     FILE *pstr = popen(cmd,"r");    
    
//     if(pstr == NULL){
//         return 0;   
//     }
 
//     char buff[512];
//     memset(buff, 0, sizeof(buff));
//     if(NULL == fgets(buff, 512, pstr)){
//         return 0;
//     }
 
//     return atoi(buff);
// }
 
// int main(int argc, char *argv[])
// {
    
//     if(argc < 2){
//         printf("Usage:test <process_name> [user]\n");
//         return 1;
//     }
    
//     unsigned int pid=0;
    
//     if(argc > 2){
//         pid = get_pid(argv[1],argv[2]);
//     }
//     else{
//         pid = get_pid(argv[1], argv[2]);
//     }
    
//     printf("pid=%d\n",pid);
//     printf("pcpu=%f\n",get_proc_cpu(pid));
//     printf("procmem=%d\n",get_proc_mem(pid));
//     printf("virtualmem=%d\n",get_proc_virtualmem(pid)); 
//     return 0;
// }

#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
typedef struct cpu_info
{
    char name[8];
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
} CPUInfo;
 
unsigned long getCPUTotalTime(CPUInfo* pstCPUInfo)
{
    return pstCPUInfo->user + pstCPUInfo->nice + pstCPUInfo->system + 
        pstCPUInfo->idle + pstCPUInfo->iowait + pstCPUInfo->irq + pstCPUInfo->softirq;
}
 
void displayCPUInfo(CPUInfo* pstCPUInfo)
{
    printf("%s %lu %lu %lu %lu %lu %lu %lu\n", pstCPUInfo->name, pstCPUInfo->user, pstCPUInfo->nice, pstCPUInfo->system,
        pstCPUInfo->idle, pstCPUInfo->iowait, pstCPUInfo->irq, pstCPUInfo->softirq);
}
 
int getCPUInfo(CPUInfo *pstCPUInfo)
{
    FILE * fp = fopen("/proc/stat", "r");
 
    char buf[1024];
    fgets(buf, sizeof(buf), fp);
 
    sscanf(buf,"%s %lu %lu %lu %lu %lu %lu %lu", 
        pstCPUInfo->name, &pstCPUInfo->user, &pstCPUInfo->nice,&pstCPUInfo->system, 
        &pstCPUInfo->idle, &pstCPUInfo->iowait, &pstCPUInfo->irq,&pstCPUInfo->softirq);  
 
    fclose(fp);
 
    return 0;
}
 
unsigned long getCPUUsageRate()
{
    CPUInfo stCPUInfo1;
    CPUInfo stCPUInfo2;
 
    memset(&stCPUInfo1, 0, sizeof(stCPUInfo1));
    memset(&stCPUInfo2, 0, sizeof(stCPUInfo2));
 
    getCPUInfo(&stCPUInfo1);
    sleep(1);
    getCPUInfo(&stCPUInfo2);
 
    unsigned long nTotalTime = getCPUTotalTime(&stCPUInfo2) - getCPUTotalTime(&stCPUInfo1);
    unsigned long nIdleTime = stCPUInfo2.idle - stCPUInfo1.idle;
    if (nTotalTime == 0)
    {
        return 0;
    }
 
    unsigned long usage = (nTotalTime - nIdleTime) * 100 / nTotalTime;
 
    return usage;
}
 
int main()
{
    for (; ; )
    {
        printf("CPU usage: %lu%%\n", getCPUUsageRate());
        sleep(3);
    }
    
    return 0;
}