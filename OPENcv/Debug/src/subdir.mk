################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Action.cpp \
../src/ActionBut.cpp \
../src/ActionInterface.cpp \
../src/Button.cpp \
../src/Detect.cpp \
../src/DetectInterface.cpp \
../src/Image.cpp \
../src/ItemInterface.cpp \
../src/Joystick.cpp \
../src/OPENcv.cpp 

OBJS += \
./src/Action.o \
./src/ActionBut.o \
./src/ActionInterface.o \
./src/Button.o \
./src/Detect.o \
./src/DetectInterface.o \
./src/Image.o \
./src/ItemInterface.o \
./src/Joystick.o \
./src/OPENcv.o 

CPP_DEPS += \
./src/Action.d \
./src/ActionBut.d \
./src/ActionInterface.d \
./src/Button.d \
./src/Detect.d \
./src/DetectInterface.d \
./src/Image.d \
./src/ItemInterface.d \
./src/Joystick.d \
./src/OPENcv.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


