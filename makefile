CC = g++
CCFLAGS += -O3
LDFLAGS += -lOpenCL


all: openCLCompiler openCLInfo

openCLInfo: src/capsbasic.cpp
	$(CC) $(CCFLAGS) -o openCLInfo src/capsbasic.cpp $(LDFLAGS)

openCLCompiler: src/build.cpp src/tool.cpp
	$(CC) $(CCFLAGS)  -o openCLCompiler src/build.cpp src/tool.cpp $(LDFLAGS)

clean:
	rm -f openCLCompiler openCLInfo *.o

