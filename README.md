# opencl-suite<br>
Welcome to use the suite tool to help build your opencl program.<br>
If you want to install the tool, you should make you have the basic gcc and g++ compiler, and you need to have the ioc64 tool(an opencl kernel program compiler, in Intel opencl SDK, )  <br>
##Intoduction:
  ###openCLAllCompiler : an openCL kernel compiler that produces all platform/device binary code.
                      USAGE: openCLAllCompiler [SOURCE]
                      source code: src/cl-compile.c
  ###openCLCompiler    : an openCL kernel compiler that help debug kernel code syntax error.
                      Usage: ./openCLCompiler [-h | --help | fileName platformType deviceType ]
                            -h, --help     Show this help message and exit.
                            fileName       The file to be compiled.
                            platformType   The platform want to compile code. The example is 
                                            0 : Intel
                                            1 : NVIDIA
                                            2 : AMD
                            deviceType     The device want to run the code. The example is 
                                            0 : CL_DEVICE_TYPE_CPU
                                            1 : CL_DEVICE_TYPE_GPU
                                            2 : CL_DEVICE_TYPE_ACCELERATOR
                                            3 : CL_DEVICE_TYPE_DEFAULT
                                            4 : CL_DEVICE_TYPE_ALL
                      source code: src/build.cpp src/tool.cpp src/tool.h
  ###openCLInfo        : an program that can get platform/device information.
                      Usage: ./openCLInfo [-h | --help | <PLATFORM>]
                              -h, --help    Show this help message and exit.
                              <PLATFORM>    Platform name substring to select platform.
                                            Case sensitive. Default value is "Intel".
                                            In case of multiple matches, the first matching
                                            platform is selected.
                      source code: src/capsbasic.cpp
  ###openCL_E_vec_add_source : an vector add example that build kernel from source kernel code.                                                               source code: src/vec_add_source.c src/vec_add.cl
  ###openCL_E_vec_add_binary : an vector add example that build kernel from prebuild binary kernel code.                                                      source code: src/vec_add_binary.c src/vec_add.cl
  ###openCL_E_vec_add_spir   : an vector add example that build kernel from prebuild spir kernel code.                                                        source code: src/vec_add_spir.c src/vec_add.cl
  ###vec_add.bin             : prebuild binary vector add kernel that use Intel ioc64 tool .
  ###vec_add.spir32          : prebuild spir32 vector add kernel that use Intel ioc64 tool . 
  ###vec_add.spir64          : prebuild spir64 vector add kernel that use Intel ioc64 tool .
  ###openCL_E_linkTwoKernel  : an example that link two kernel file into one kernel.                                                                          source code: src/fma.c src/fma.cl src/elem.cl
  
                      




##Support:
You can get Intel openCL support from this(https://software.intel.com/en-us/intel-opencl)<br>
If you are interested openCL development on Nvidia GPU. try this(https://developer.nvidia.com/opencl)<br>
You can get AMD openCL help from this(http://developer.amd.com/tools-and-sdks/opencl-zone/)<br>
