################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU\ drivers/Wdt/io_wdt.c 

OBJS += \
./Sources/MCU\ drivers/Wdt/io_wdt.o 

C_DEPS += \
./Sources/MCU\ drivers/Wdt/io_wdt.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU\ drivers/Wdt/io_wdt.o: ../Sources/MCU\ drivers/Wdt/io_wdt.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Wdt/io_wdt.d" -MT"Sources/MCU\ drivers/Wdt/io_wdt.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


