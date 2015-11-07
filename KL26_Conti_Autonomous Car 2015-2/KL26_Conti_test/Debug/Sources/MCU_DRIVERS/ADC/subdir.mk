################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU_DRIVERS/ADC/io_adc.c \
../Sources/MCU_DRIVERS/ADC/io_adc_cnf.c 

OBJS += \
./Sources/MCU_DRIVERS/ADC/io_adc.o \
./Sources/MCU_DRIVERS/ADC/io_adc_cnf.o 

C_DEPS += \
./Sources/MCU_DRIVERS/ADC/io_adc.d \
./Sources/MCU_DRIVERS/ADC/io_adc_cnf.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU_DRIVERS/ADC/%.o: ../Sources/MCU_DRIVERS/ADC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


