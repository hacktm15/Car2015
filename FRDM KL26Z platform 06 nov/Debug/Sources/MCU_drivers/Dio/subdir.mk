################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU_drivers/Dio/io_dio.c 

OBJS += \
./Sources/MCU_drivers/Dio/io_dio.o 

C_DEPS += \
./Sources/MCU_drivers/Dio/io_dio.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU_drivers/Dio/%.o: ../Sources/MCU_drivers/Dio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"../Sources" -I"../Includes" -std=c99 -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


