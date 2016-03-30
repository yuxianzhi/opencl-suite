#ifndef __TOOLH__
#define __TOOLH__
#include <CL/cl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

extern int deviceTypeNum;
extern cl_device_type deviceTypeList[];
extern char* deviceTypeName[];

extern int platformTypeNum;
extern char* platformTypeName[];

/** convert the kernel file into a string */
int convertToString(const char *filename, std::string& s);

/**Getting platforms and choose an available one.*/
int getPlatform(cl_platform_id &platform, int id);

/**Step 2:Query the platform and choose the first GPU device if has one.*/
cl_device_id *getCl_device_id(cl_platform_id &platform, int deviceType);

/**获取编译program出错时，编译器的出错信息*/
int getProgramBuildInfo(cl_program program,cl_device_id device);
#endif
