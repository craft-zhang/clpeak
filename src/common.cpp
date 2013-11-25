
#include <common.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

device_info_t getDeviceInfo(cl::Device &d)
{
    device_info_t devInfo;
    
    devInfo.numCUs = d.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
    devInfo.maxWGSize = d.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
    // Limiting max work-group size to 256
    #define MAX_WG_SIZE 256
    devInfo.maxWGSize = MIN(devInfo.maxWGSize, MAX_WG_SIZE);
    
    devInfo.maxAllocSize = d.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();
    devInfo.maxGlobalSize = d.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
    devInfo.doubleSupported = false;
    
    std::string extns = d.getInfo<CL_DEVICE_EXTENSIONS>();
    if((extns.find("cl_khr_fp64") != std::string::npos) || (extns.find("cl_amd_fp64") != std::string::npos))
        devInfo.doubleSupported = true;
    
    return devInfo;
}


void populate(float *ptr, uint N)
{
    srand(time(NULL));

    for(int i=0; i<(int)N; i++)
    {
        //ptr[i] = (float)rand();
        ptr[i] = (float)i;
    }
}

void populate(double *ptr, uint N)
{
    srand(time(NULL));

    for(int i=0; i<(int)N; i++)
    {
        //ptr[i] = (double)rand();
        ptr[i] = (double)i;
    }
}

#define MAX_POWER   25
uint roundToPowOf2(uint number)
{
    float logd = log(number) / log(2);
    logd = floor(logd);
    logd = MIN(logd, MAX_POWER);
    
    return pow(2, (int)logd);
}
