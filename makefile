CPP = g++
CC = gcc
CCFLAGS += -O3 -DCL_USE_DEPRECATED_OPENCL_2_0_APIS=1
LDFLAGS += -lOpenCL

OUT := openCLCompiler openCLInfo openCLAllCompiler \
		openCL_E_linkTwoKernel \
		openCL_E_vec_add_source openCL_E_vec_add_binary openCL_E_vec_add_spir vec_add.bin vec_add.spir32 vec_add.spir64

all: $(OUT)

openCLInfo: src/capsbasic.cpp
	$(CPP) $(CCFLAGS) -o openCLInfo src/capsbasic.cpp $(LDFLAGS)

openCLCompiler: src/build.cpp src/tool.cpp
	$(CPP) $(CCFLAGS)  -o openCLCompiler src/build.cpp src/tool.cpp $(LDFLAGS)

openCLAllCompiler: src/cl-compile.c
	$(CC) $(CCFLAGS)  -o openCLAllCompiler src/cl-compile.c $(LDFLAGS)

openCL_E_linkTwoKernel: src/fma.c
	$(CC) $(CCFLAGS)  -o openCL_E_linkTwoKernel src/fma.c $(LDFLAGS)

openCL_E_vec_add_source: src/vec_add_source.c
	$(CC) $(CCFLAGS)  -o openCL_E_vec_add_source src/vec_add_source.c $(LDFLAGS)

openCL_E_vec_add_binary: src/vec_add_binary.c
	$(CC) $(CCFLAGS)  -o openCL_E_vec_add_binary src/vec_add_binary.c $(LDFLAGS)

openCL_E_vec_add_spir: src/vec_add_spir.c
	$(CC) $(CCFLAGS)  -o openCL_E_vec_add_spir src/vec_add_spir.c $(LDFLAGS)


vec_add.bin: src/vec_add.cl
	ioc64 -cmd=build -input=$< -ir=$@

vec_add.spir32: src/vec_add.cl
	ioc64 -cmd=build -input=$< -spir32=$@

vec_add.spir64: src/vec_add.cl
	ioc64 -cmd=build -input=$< -spir64=$@

clean:
	rm -f $(OUT) *.o

