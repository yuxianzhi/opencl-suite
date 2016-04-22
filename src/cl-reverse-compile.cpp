 #include "tool.h"
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>
 #include <string>
 #include <fstream>
 using namespace std;
 
//
///
//  Retreive program binary for all of the devices attached to the
//  program an and store the one for the device passed in
//
bool SaveProgramBinary(cl_program program, cl_device_id device, const char* fileName)
{
    cl_uint numDevices = 0;
    cl_int errNum;

    // 1 - Query for number of devices attached to program
    errNum = clGetProgramInfo(program, CL_PROGRAM_NUM_DEVICES, sizeof(cl_uint),
                              &numDevices, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error querying for number of devices." << std::endl;
        return false;
    }

    // 2 - Get all of the Device IDs
    cl_device_id *devices = new cl_device_id[numDevices];
    errNum = clGetProgramInfo(program, CL_PROGRAM_DEVICES,
                              sizeof(cl_device_id) * numDevices,
                              devices, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error querying for devices." << std::endl;
        delete [] devices;
        return false;
    }

    // 3 - Determine the size of each program binary
    size_t *programBinarySizes = new size_t [numDevices];
    errNum = clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES,
                              sizeof(size_t) * numDevices,
                              programBinarySizes, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error querying for program binary sizes." << std::endl;
        delete [] devices;
        delete [] programBinarySizes;
        return false;
    }

    unsigned char **programBinaries = new unsigned char*[numDevices];
    for (cl_uint i = 0; i < numDevices; i++)
    {
        programBinaries[i] = new unsigned char[programBinarySizes[i]];
    }

    // 4 - Get all of the program binaries
    errNum = clGetProgramInfo(program, CL_PROGRAM_BINARIES, sizeof(unsigned char*) * numDevices,
                              programBinaries, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error querying for program binaries" << std::endl;

        delete [] devices;
        delete [] programBinarySizes;
        for (cl_uint i = 0; i < numDevices; i++)
        {
            delete [] programBinaries[i];
        }
        delete [] programBinaries;
        return false;
    }

    // 5 - Finally store the binaries for the device requested out to disk for future reading.
    for (cl_uint i = 0; i < numDevices; i++)
    {
        // Store the binary just for the device requested.  In a scenario where
        // multiple devices were being used you would save all of the binaries out here.
        if (devices[i] == device)
        {
            FILE *fp = fopen(fileName, "wb");
            fwrite(programBinaries[i], 1, programBinarySizes[i], fp);
            fclose(fp);
            break;
        }
    }

    // Cleanup
    delete [] devices;
    delete [] programBinarySizes;
    for (cl_uint i = 0; i < numDevices; i++)
    {
        delete [] programBinaries[i];
    }
    delete [] programBinaries;
    return true;
}


void getName(char *out, char *in, int platformType, int deviceType)
{
	sprintf(out, "%s-%s-%s.bin", in, platformTypeName[platformType], deviceTypeName[deviceType]);
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
     status=clBuildProgram(program, 1, devices,NULL,NULL,NULL);
     if(status < 0)    //get the build info
         getProgramBuildInfo(program ,devices[0]);
     else
         printf("\nProgram Build Success. \n");

	 char *binFile = (char *)malloc(sizeof(char)*200);
	 getName(binFile, fileName, platformType, deviceType);
	 //save program to file
     SaveProgramBinary(program, devices[0], binFile);
	 printf("binary file has been writen to file %s\nCongratulation!!!\n\n", binFile);
	 free(binFile);


     status = clReleaseProgram(program);    //Release the program object.
     status = clReleaseContext(context);//Release context.
     free(devices);
     return 0;
 }
