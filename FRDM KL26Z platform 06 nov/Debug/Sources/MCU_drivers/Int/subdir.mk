################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU_drivers/Int/io_int.c \
../Sources/MCU_drivers/Int/io_int_cnf.c 

OBJS += \
./Sources/MCU_drivers/Int/io_int.o \
./Sources/MCU_drivers/Int/io_int_cnf.o 

C_DEPS += \
./Sources/MCU_drivers/Int/io_int.d \
./Sources/MCU_drivers/Int/io_int_cnf.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU_drivers/Int/%.o: ../Sources/MCU_drivers/Int/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"../Sources" -I"../Includes" -std=c99 -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


