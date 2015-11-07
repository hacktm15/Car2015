################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/HW_drivers/H-bridge/ti8833/io_hbr_cnf_ti8833.c \
../Sources/HW_drivers/H-bridge/ti8833/io_hbr_ti8833.c 

OBJS += \
./Sources/HW_drivers/H-bridge/ti8833/io_hbr_cnf_ti8833.o \
./Sources/HW_drivers/H-bridge/ti8833/io_hbr_ti8833.o 

C_DEPS += \
./Sources/HW_drivers/H-bridge/ti8833/io_hbr_cnf_ti8833.d \
./Sources/HW_drivers/H-bridge/ti8833/io_hbr_ti8833.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/HW_drivers/H-bridge/ti8833/%.o: ../Sources/HW_drivers/H-bridge/ti8833/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"../Sources" -I"../Includes" -std=c99 -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


