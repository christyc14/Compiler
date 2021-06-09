#!/bin/bash

compiler="bin/c_compiler"

input_dir="compiler_tests_organized"
input_dir_prog="compiler_tests_organized/programs"

working="tmp/tests"
mkdir -p ${working}
declare -i counter_pass
declare -i counter
counter_pass=0
counter=0

for i in ${input_dir_prog}/*.c ; do #for a specific type test, do /"integer_"*.c
#types are: array, control_flow, functions, integer, misc, test, float, local_var, pointer, progs, strings, struct, types
#i=${input_dir_prog}/test_ADD0.c
  base=$(echo $i | sed -E -e "s|${input_dir_prog}/([^.]+)[.]c|\1|g");
  echo -e "\e[1;34m Creating assembly code for: $base.c \e[0m"
  base_driver=$(echo $base | sed -E -e "s|$|_driver|g")
  #echo -e "\e[1;33m $base_driver \e[0m"
  $compiler -S $i -o ${working}/$base.s
  dot_s=${working}/$base.s
  echo -e "\e[1;33m Making object file \e[0m"
  mips-linux-gnu-gcc -mfp32 -o ${working}/$base.o -c ${working}/$base.s
  dot_o=${working}/$base.o
  echo -e "\e[1;33m Linking driver \e[0m"
  mips-linux-gnu-gcc -mfp32 -static -o ${working}/$base ${working}/$base.o ${input_dir}/drivers/$base_driver.c
  echo -e "\e[1;33m Testing with QEMU \e[0m"
  qemu-mips ${working}/$base

  if [[ $? == 0 ]]; then
    #statements
    echo -e "\e[1;32m $i, Pass \e[0m"
    counter_pass+=1
  else
    echo -e "\e[1;31m $i, Fail \n Exit code $? \e[0m"
  fi

  counter+=1
done
echo -e "\e[1;35m Passed $counter_pass tests out of $counter\e[0m"
