 #include "tool.h"
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>
 #include <string>
 #include <fstream>
 using namespace std;
 
extern int deviceTypeNum;
extern cl_device_type deviceTypeList[];

 void CL_CALLBACK checkData(cl_program platform, void* data){
     printf("%s\n",(char*)data);
 }
 
 int main(int argc, char* argv[])
 {
	 char buffer[100];
     char *fileName;
	 int platformType;
	 int deviceType;
#if 0
	 fileName = buffer;
     printf("Please input opencl kernel file name\n");
	 scanf("%s", &buffer);
	 printf("\n");
     printf("Please input platform type(a number)\n");
	 printf("0 : Intel\n");
	 printf("1 : NVIDIA\n");
	 printf("2 : AMD\n");
	 scanf("%d", &platformType);
	 printf("\n");
     printf("Please input device type(a number)\n");
	 printf("0 : CL_DEVICE_TYPE_CPU\n");
	 printf("1 : CL_DEVICE_TYPE_GPU\n");
	 printf("2 : CL_DEVICE_TYPE_ACCELERATOR\n");
	 printf("3 : CL_DEVICE_TYPE_DEFAULT\n");
	 printf("4 : CL_DEVICE_TYPE_ALL\n");
	 scanf("%d", &deviceType);
	 printf("\n");
#else
    // Sample accepts one optional argument only, see usage information below
    if(argc > 4)
    {
        cerr << "Error: too many command line arguments.\n";
    }

    // Print usage information in case
    if(
        argc > 4 ||     // ... when wrong number of arguments is provided
        argc == 2 && (  // or user asks for help
        strcmp(argv[1], "-h") == 0 ||
        strcmp(argv[1], "--help") == 0
        )
        )
    {
        cout
            << "Usage: " << argv[0] << " [-h | --help | fileName platformType deviceType ]\n\n"
            << "    -h, --help     Show this help message and exit.\n\n"
            << "    fileName       The file to be compiled.\n\n"
            << "    platformType   The platform want to compile code. The example is \n"
            << "                   0 : Intel\n"
            << "                   1 : NVIDIA\n"
            << "                   2 : AMD\n\n"
            << "    deviceType     The device want to run the code. The example is \n"
            << "                   0 : CL_DEVICE_TYPE_CPU\n"
            << "                   1 : CL_DEVICE_TYPE_GPU\n"
            << "                   2 : CL_DEVICE_TYPE_ACCELERATOR\n"
            << "                   3 : CL_DEVICE_TYPE_DEFAULT\n"
            << "                   4 : CL_DEVICE_TYPE_ALL\n\n";

        exit(argc > 4); // return non-zero only if an error occurs
    }

    if(argc == 4)
    {
        // User provided substring for platform name selection:
	 	fileName   = argv[1];
	 	platformType = atoi(argv[2]);
	 	deviceType = atoi(argv[3]);
    }
#endif
	 printf("\nThe file to be compiled  : %s\n", fileName);
	 if(platformType < 0 || platformType >= platformTypeNum)
		platformType = 0;
	 printf("The platform type        : %s\n", platformTypeName[platformType]);
	 if(deviceType < 0 || deviceType >= deviceTypeNum)
		deviceType = 3;
	 printf("The device   type        : %s\n\n", deviceTypeName[deviceType]);


     cl_int    status;
     /** Getting platforms and choose an available one(first).*/
     cl_platform_id platform;
     getPlatform(platform, platformType);
 
     /**Query the platform and choose the device.*/
     cl_device_id *devices=getCl_device_id(platform, deviceType);
 
     /**Create context use the frist device.*/
     cl_context context = clCreateContext(NULL,1, devices,NULL,NULL,NULL);
 
     /**Create program object */
     string sourceStr;
     status = convertToString(fileName, sourceStr);
     const char *source = sourceStr.c_str();
     size_t sourceSize[] = {strlen(source)};
     cl_program program = clCreateProgramWithSource(context, 1, &source, sourceSize, NULL);
 
     /**Build program. */
     //status=clBuildProgram(program, 1,devices,NULL,checkData,"sdf");
     status=clBuildProgram(program, 1,devices,NULL,NULL,NULL);
     if(status < 0)    //get the build info
         getProgramBuildInfo(program ,devices[0]);
     else
         printf("\nProgram Build Success. \nCongratulations!\n\n");
     
     status = clReleaseProgram(program);    //Release the program object.
     status = clReleaseContext(context);//Release context.
     free(devices);
     return 0;
 }
