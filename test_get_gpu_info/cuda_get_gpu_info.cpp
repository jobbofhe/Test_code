
#include <iostream>
#include <cuda.h>
#include <cuda_runtime.h>


int main()
{
    size_t freeMemory, totalMemory;

    cudaMemGetInfo(&freeMemory, &totalMemory);
    
    std::cout << "===========================================================" << std::endl;
    std::cout << "Free/Total(kB): " << freeMemory/1024 << "/" << totalMemory/1024 << std::endl;
    std::cout << "Free/Total(MB): " << freeMemory/1024/1024 << "/" << totalMemory/1024/1024 << std::endl;
}