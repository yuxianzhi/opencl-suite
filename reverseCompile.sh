#!/bin/sh

echo "The script use objdump tool disassembly the binary kernel(created by openCLReverseCompiler)"
echo "usage: ./reverseCompile.sh file1 file2"
echo "                           file1 : the binary kernel(created by openCLReverseCompiler)"
echo "                           file2 : the output file"
if  test $# -eq 2; then 
  echo "The binary kernel : $1"
  echo "The output file   : $2"
  which objdump > /dev/null 2>&1
  if [ $? == 0 ]; then
    objdump -D -b binary -m i386 $1 > $2
    echo "Success!!"
  else
    echo "objdump is not installed in your system."
  fi
else
  echo "command can't been recognized"
  exit;
fi
