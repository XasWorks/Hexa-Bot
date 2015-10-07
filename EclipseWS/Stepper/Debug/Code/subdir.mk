################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Code/LCD.cpp 

OBJS += \
./Code/LCD.o 

CPP_DEPS += \
./Code/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
Code/%.o: ../Code/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


