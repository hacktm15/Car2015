################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/HW_drivers/H-bridge/tb6612fng/io_hbr_cnf_tb6612.c \
../Sources/HW_drivers/H-bridge/tb6612fng/io_hbr_tb6612.c 

OBJS += \
./Sources/HW_drivers/H-bridge/tb6612fng/io_hbr_cnf_tb6612.o \
./Sources/HW_drivers/H-bridge/tb6612fng/io_hbr_tb6612.o 

C_DEPS += \
./Sources/HW_drivers/H-bridge/tb6612fng/io_hbr_cnf_tb6612.d \
./Sources/HW_drivers/H-bridge/tb6612fng/io_hbr_tb6612.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/HW_drivers/H-bridge/tb6612fng/%.o: ../Sources/HW_drivers/H-bridge/tb6612fng/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"../Sources" -I"../Includes" -std=c99 -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


