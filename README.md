# opencl-suite<br>
Welcome to use the suite tool to help build your opencl program.<br>
If you want to install the tool, you should make you have the basic gcc and g++ compiler, and you need to have the ioc64 tool(an opencl kernel program compiler, in Intel opencl SDK, )  <br> 
##Intoduction:
  ###openCLAllCompiler : an openCL kernel compiler that produces all platform/device binary code. <br> 
                      USAGE: openCLAllCompiler [SOURCE]  <br>
                      source code: src/cl-compi <br>
  ###openCLCompiler    : an openCL kernel compiler that help debug kernel code syntax error. <br>
                      Usage: ./openCLCompiler [-h | --help | fileName platformType deviceType ] <br>
                            -h, --help     Show this help message and exit. <br>
                            fileName       The file to be compiled. <br>
                            platformType   The platform want to compile code. The example is  <br>
                                            0 : Intel <br>
                                            1 : NVIDIA <br> 
                                            2 : AMD <br>
                            deviceType     The device want to run the code. The example is  <br>
                                            0 : CL_DEVICE_TYPE_CPU <br>
                                            1 : CL_DEVICE_TYPE_GPU <br>
                                            2 : CL_DEVICE_TYPE_ACCELERATOR <br>
                                            3 : CL_DEVICE_TYPE_DEFAULT <br>
                                            4 : CL_DEVICE_TYPE_ALL <br>
                      source code: src/build.cpp src/tool.cpp src/tool.h <br>
  ###openCLInfo        : an program that can get platform/device information. <br>
                      Usage: ./openCLInfo [-h | --help | <PLATFORM>] <br>
                              -h, --help    Show this help message and exit. <br>
                              <PLATFORM>    Platform name substring to select platform. <br>
                                            Case sensitive. Default value is "Intel". <br>
                                            In case of multiple matches, the first matching <br>
                                            platform is selected. <br>
                      source code: src/capsbasic.cpp <br>
  ###openCL_E_vec_add_source : an vector add example that build kernel from source kernel code. <br>                                                          source code: src/vec_add_source.c src/vec_add.cl <br>
  ###openCL_E_vec_add_binary : an vector add example that build kernel from prebuild binary kernel code.  <br>                                                source code: src/vec_add_binary.c src/vec_add.cl <br>
  ###openCL_E_vec_add_spir   : an vector add example that build kernel from prebuild spir kernel code. <br>                                                   source code: src/vec_add_spir.c src/vec_add.cl <br>
  ###vec_add.bin             : prebuild binary vector add kernel that use Intel ioc64 tool .<br>
  ###vec_add.spir32          : prebuild spir32 vector add kernel that use Intel ioc64 tool .<br>
  ###vec_add.spir64          : prebuild spir64 vector add kernel that use Intel ioc64 tool .<br>
  ###openCL_E_linkTwoKernel  : an example that link two kernel file into one kernel.  <br>                                                                    source code: src/fma.c src/fma.cl src/elem.cl <br>
  
                      




##Support:
You can get Intel openCL support from this(https://software.intel.com/en-us/intel-opencl)<br>
If you are interested openCL development on Nvidia GPU. try this(https://developer.nvidia.com/opencl)<br>
You can get AMD openCL help from this(http://developer.amd.com/tools-and-sdks/opencl-zone/)<br>
