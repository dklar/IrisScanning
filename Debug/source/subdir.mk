################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sine.cpp \
../toplevel.cpp 

OBJS += \
./source/sine.o \
./source/toplevel.o 

CPP_DEPS += \
./source/sine.d \
./source/toplevel.d 


# Each subdirectory must supply rules for building sources it contributes
source/sine.o: C:/Users/Dennis/VivadoHLS/Final/Iris-recognition/sine.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Xilinx/Vivado/2019.2/include -IC:/Users/Dennis/VivadoHLS/Final -IC:/Xilinx/Vivado/2019.2/include/etc -IC:/Xilinx/Vivado/2019.2/win64/tools/systemc/include -IC:/Xilinx/Vivado/2019.2/include/ap_sysc -IC:/Xilinx/Vivado/2019.2/win64/tools/auto_cc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/toplevel.o: C:/Users/Dennis/VivadoHLS/Final/Iris-recognition/toplevel.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -IC:/Xilinx/Vivado/2019.2/include -IC:/Users/Dennis/VivadoHLS/Final -IC:/Xilinx/Vivado/2019.2/include/etc -IC:/Xilinx/Vivado/2019.2/win64/tools/systemc/include -IC:/Xilinx/Vivado/2019.2/include/ap_sysc -IC:/Xilinx/Vivado/2019.2/win64/tools/auto_cc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


