################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU\ drivers/Adc/io_adc.c \
../Sources/MCU\ drivers/Adc/io_adc_cnf.c 

OBJS += \
./Sources/MCU\ drivers/Adc/io_adc.o \
./Sources/MCU\ drivers/Adc/io_adc_cnf.o 

C_DEPS += \
./Sources/MCU\ drivers/Adc/io_adc.d \
./Sources/MCU\ drivers/Adc/io_adc_cnf.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU\ drivers/Adc/io_adc.o: ../Sources/MCU\ drivers/Adc/io_adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Adc/io_adc.d" -MT"Sources/MCU\ drivers/Adc/io_adc.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/MCU\ drivers/Adc/io_adc_cnf.o: ../Sources/MCU\ drivers/Adc/io_adc_cnf.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Adc/io_adc_cnf.d" -MT"Sources/MCU\ drivers/Adc/io_adc_cnf.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


