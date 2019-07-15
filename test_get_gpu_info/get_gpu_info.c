
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define GPU_INFO_LEN    (4096)

// int get_gpu_available_space(int gpuId, char *nvidiaSmiInfo)
// {
//     int availableSize = 0;
//     char *pGpuInfo = nvidiaSmiInfo;

//     char *pLine = strtok(pGpuInfo, "\n");
//     int lineCount = 0;

//     while( pLine != NULL )
//     {
//         pLine = strtok( NULL, "\n" );
//         lineCount++;
//         if (gpuId == 0 && lineCount == 8)
//         {
//            break;
//         }

//         if (gpuId == 1 && lineCount == 11)
//         {
//            break;
//         }
//     }

//     char totalSize[32];
//     char usedSize[32];

//     char *pUsed = strtok(pLine, " ");

//     int spaceCount = 0;
//     while( pUsed != NULL ) 
//     {
//         pUsed = strtok(NULL, " ");
//         spaceCount++;
//         if (spaceCount == 8)
//         {   
//             strcpy(usedSize, pUsed);
//         }
//         if(spaceCount == 10)
//         {
//             strcpy(totalSize, pUsed);
//             break;
//         }
//     }

//     availableSize = atoi(totalSize) - atoi(usedSize);

//     char total[16];
//     char used[16];
//     strncpy(total, totalSize, strlen(totalSize) - 3);
//     strncpy(used, usedSize, strlen(usedSize) - 3);
//     // printf("totalSize [%s] usedSize [%s] \navailableSize[%d]\n", total, used, atoi(total) - atoi(used));

//     return availableSize;
// }



// int get_gpu_info(char *gpuInfo)
// {
//     if (NULL == gpuInfo)
//     {
//         return -1;
//     }

//     system("nvidia-smi >/icooper/log/nvidia-smi.log");

//     FILE *fd = fopen("/icooper/log/nvidia-smi.log", "r");

//     char buf_ps[256]; 

//     while(fgets(buf_ps, 100, fd) != NULL)   
//     {   
//        strcat(gpuInfo, buf_ps);   
//        if(strlen(gpuInfo)>GPU_INFO_LEN)   
//            break;   
//     }   
// }



int get_gpu_info(char *gpuInfo)
{
    if (NULL == gpuInfo)
    {
        return -1;
    }
    char buf_ps[1024]; 
    FILE *fd = popen("nvidia-smi -q -i 0,1 -d Temperature", "r");

    while(fgets(buf_ps, 128, fd) != NULL)   
    {   
       strcat(gpuInfo, buf_ps);   
       if(strlen(gpuInfo)>1024)   
           break;   
    }   
}

int get_gpu_temprature(char *gpuInfo)
{
    char *pUsed = strtok(gpuInfo, "\n");
    char temp[32] = {0};
    memset(temp, 0, sizeof(temp));

    while( pUsed != NULL ) 
    {
        pUsed = strtok(NULL, "\n");
        if (strstr(pUsed, "Current"))
        {
            break;
        }
    }

    char *pTemp = strstr(pUsed, ":");
    char temprature[32];
    memset(temprature, 0, sizeof(temprature));
    strncpy(temprature, pTemp+2, sizeof(temprature));

    return atoi(temprature);
}

int main()
{
    for (;;)
    {
        char result[1024];
        get_gpu_info(result);

        // printf("[%s]\n", result);
     
        int temprature = get_gpu_temprature(result);

        printf("availableSize [%d]\n", temprature);
        sleep(1);
    }

    return 0;
}



// int getGpuInfo(char *gpuInfo)
// {
//     if (NULL == gpuInfo)
//     {
//         return -1;
//     }

//     system("nvidia-smi >/icooper/log/nvidia-smi.log");

//     FILE *fd = fopen("/icooper/log/nvidia-smi.log", "r");

//     char buf_ps[256]; 

//     while(fgets(buf_ps, 100, fd) != NULL)   
//     {   
//         strcat(gpuInfo, buf_ps);   
//         if (strlen(gpuInfo) > GPU_INFO_LEN)   
//         {
//             break;
//         }  
//     }   
//     fclose(fd);

//     return 0;
// }

// int getGpuAvailableSpace(int gpuId, char *nvidiaSmiInfo)
// {
//     int availableSize = 0;
//     char *pGpuInfo = nvidiaSmiInfo;
//     char *pLine = strtok(pGpuInfo, "\n");
//     int lineCount = 0;

//     while( pLine != NULL )
//     {
//         pLine = strtok( NULL, "\n" );
//         lineCount++;
//         // 提取nvidia-smi 结果的第9行信息
//         if (gpuId == 0 && lineCount == 8)
//         {
//            break;
//         }
//         // 提取nvidia-smi 结果的第12行信息
//         if (gpuId == 1 && lineCount == 11)
//         {
//            break;
//         }
//     }

//     char totalSize[32];
//     char usedSize[32];
//     char *pUsed = strtok(pLine, " ");
//     int spaceCount = 0;

//     while( pUsed != NULL ) 
//     {
//         pUsed = strtok(NULL, " ");
//         spaceCount++;
//         // 提取nvidia-smi 结果的第9行信息的第9个字段
//         if (spaceCount == 8)
//         {   
//             strcpy(usedSize, pUsed);
//         }
//         // 提取nvidia-smi 结果的第9行信息的第11个字段
//         if(spaceCount == 10)
//         {
//             strcpy(totalSize, pUsed);
//             break;
//         }
//     }

//     availableSize = atoi(totalSize) - atoi(usedSize);

//     char total[16];
//     char used[16];
//     strncpy(total, totalSize, strlen(totalSize) - 3);
//     strncpy(used, usedSize, strlen(usedSize) - 3);

//     return availableSize;
// }

// int gpuMemoryIsFull(int minSize)
// {
//     char gpuInfo[GPU_INFO_LEN];
//     getGpuInfo(gpuInfo);
//     int availableSize = getGpuAvailableSpace(0, gpuInfo);
    
//     if (availableSize < minSize)
//     {
//         return GPU_SPACE_IS_FULL;
//     }
//     else
//     {
//         return GPU_SPACE_IS_FREE;
//     }
// }




/**
 * 获取GPU 使用率
 */
// #include <stdlib.h>
// #include <stdio.h>
// #include <cuda.h>
// #include <cuda_runtime.h>

// int main()
// {
//     int i = 0;
//     cudaSetDevice(0);
//     for (i; i < 10; i++)
//     {
//         size_t freeMemory, totalMemory;

//         cudaMemGetInfo(&freeMemory, &totalMemory);
        
//         printf("Free/Total(MB): %zu/%zu\n", freeMemory/1024/1024, totalMemory/1024/1024);
//         printf("[%d]\n", (int)(freeMemory/1024/1024));

//         printf("usage [%f]\n", (totalMemory - freeMemory) /(float)totalMemory);
//         sleep(6);
//     }
    
//     return 0;
// }
