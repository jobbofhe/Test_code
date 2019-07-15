
#include <stdio.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>

void visionGetGpuFreeMemorySize(int *freeSize, int *totalsize, int gpuNumber)
{
    size_t freeMemory, totalMemory;
    int ret = cudaSetDevice(gpuNumber);
    cudaMemGetInfo(&freeMemory, &totalMemory);
    freeMemory = freeMemory/1024/1024;
    totalMemory = totalMemory/1024/1024;
    *freeSize = (int)freeMemory;
    *totalsize = (int)totalMemory;
}


int getDeviceIdByTaskCount(int taskCount, int step)
{   
    int deviceId = -1;
    int i = 0;
    for (i; i < taskCount; ++i)
    {
        if (i % step == 0)
        {
            deviceId++;
        }
    }

    return deviceId;
}

int main()
{
    int freeMemory = 0;
    int totalMemory = 0;

    visionGetGpuFreeMemorySize(&freeMemory, &totalMemory, 0);
    printf("gpu [%d], free [%d], tottal [%d]\n", 0, freeMemory, totalMemory);

    visionGetGpuFreeMemorySize(&freeMemory, &totalMemory, 1);
    printf("gpu [%d], free [%d], total [%d]\n", 1, freeMemory, totalMemory);


    int dev = 0;
    cudaGetDevice(&dev);
    printf("cudaGetDevice [%d]\n", dev);

    cudaGetDeviceCount(&dev);
    printf("cudaGetDeviceCount [%d]\n", dev);


    int device = -1;
    int i;
    for (i = 0; i < 16; i++)
    {
        if (i % 4 == 0)
        {
            device++;
            printf("[%d]\n", device);
        }
    }

    printf("deviceId: [%d]\n", getDeviceIdByTaskCount(16, 4));

    return 0;
}