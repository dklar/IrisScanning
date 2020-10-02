################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../testfile.cpp 

OBJS += \
./testbench/testfile.o 

CPP_DEPS += \
./testbench/testfile.d 


# Each subdirectory must supply rules for building sources it contributes
testbench/testfile.o: C:/Users/Dennis/VivadoHLS/Final/Iris-recognition/testfile.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Xilinx/Vivado/2019.2/include -IC:/Users/Dennis/VivadoHLS/Final -IC:/Xilinx/Vivado/2019.2/include/etc -IC:/Xilinx/Vivado/2019.2/win64/tools/systemc/include -IC:/Xilinx/Vivado/2019.2/include/ap_sysc -IC:/Xilinx/Vivado/2019.2/win64/tools/auto_cc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


