 #include <CL/cl.h>
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>
 #include <string>
 #include <fstream>
 #include "tool.h"
 using namespace std;

int deviceTypeNum = 5;
cl_device_type deviceTypeList[5] = {CL_DEVICE_TYPE_CPU, CL_DEVICE_TYPE_GPU, CL_DEVICE_TYPE_ACCELERATOR, CL_DEVICE_TYPE_DEFAULT, CL_DEVICE_TYPE_ALL};
char* deviceTypeName[5] = {"CPU", "GPU", "ACCELERATOR(MIC/DSP)", "DEFAULT", "ALL"};

int platformTypeNum = 3;
char* platformTypeName[3]={"Intel(R) OpenCL", "NVIDIA CUDA", "ATI Stream"};

 /** convert the kernel file into a string */
 int convertToString(const char *filename, std::string& s)
 {
     size_t size;
     char*  str;
     std::fstream f(filename, (std::fstream::in | std::fstream::binary));
 
     if(f.is_open())
     {
         size_t fileSize;
         f.seekg(0, std::fstream::end);
         size = fileSize = (size_t)f.tellg();
         f.seekg(0, std::fstream::beg);
         str = new char[size+1];
         if(!str)
         {
             f.close();
             return 0;
         }
 
         f.read(str, fileSize);
         f.close();
         str[size] = '\0';
         s = str;
         delete[] str;
         return 0;
     }
     cout<<"Error: failed to open file\n:"<<filename<<endl;
     return -1;
 }
 
 /**Getting platforms and choose an available one.*/
 int getPlatform(cl_platform_id &platform, int id)
 {
     platform = NULL;//the chosen platform
 
     cl_uint numPlatforms;//the NO. of platforms
     cl_int    status = clGetPlatformIDs(0, NULL, &numPlatforms);
     if (status != CL_SUCCESS)
     {
         cout<<"Error: Getting platforms!"<<endl;
         return -1;
     }
 
     /**For clarity, choose the first available platform. */
     if(numPlatforms > 0)
     {
         cl_platform_id* platforms =
             (cl_platform_id* )malloc(numPlatforms* sizeof(cl_platform_id));
         status = clGetPlatformIDs(numPlatforms, platforms, NULL);
		 for(int i=0; i<numPlatforms; i++){
			size_t size;
			clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &size);
			char *name = (char *)malloc(sizeof(char)*size);
			clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, size, name, NULL);
			if(strcmp(name, platformTypeName[id])==0){
				//printf("platform %s\n", name);
         		platform = platforms[i];
         		free(platforms);
				free(name);
				return 0;
			}
		 }	
         platform = platforms[0];
         free(platforms);
     }
     else
         return -1;
 }
 
 /**Step 2:Query the platform and choose the GPU device*/
 cl_device_id *getCl_device_id(cl_platform_id &platform, int deviceType)
 {
     cl_uint numDevices = 0;
     cl_device_id *devices=NULL;
     cl_int    status = clGetDeviceIDs(platform, deviceTypeList[deviceType], 0, NULL, &numDevices);
     if (numDevices > 0) //available.
     {
         devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
         status = clGetDeviceIDs(platform, deviceTypeList[deviceType], numDevices, devices, NULL);
     }
     return devices;
 }
 
 /**获取编译program出错时，编译器的出错信息*/
 int getProgramBuildInfo(cl_program program,cl_device_id device)
 {
     size_t log_size;
     char *program_log;
     /* Find size of log and print to std output */
     clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 
             0, NULL, &log_size);
     program_log = (char*) malloc(log_size+1);
     program_log[log_size] = '\0';
     clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 
             log_size+1, program_log, NULL);
     printf("%s\n", program_log);
     free(program_log);
     return 0;
 }

