################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ArimethicCoder.cpp \
../ModelI.cpp \
../ModelOrder0C.cpp \
../main.cpp 

OBJS += \
./ArimethicCoder.o \
./ModelI.o \
./ModelOrder0C.o \
./main.o 

CPP_DEPS += \
./ArimethicCoder.d \
./ModelI.d \
./ModelOrder0C.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


