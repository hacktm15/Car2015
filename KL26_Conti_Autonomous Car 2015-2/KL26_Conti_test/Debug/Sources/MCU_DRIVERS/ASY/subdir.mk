################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU_DRIVERS/ASY/io_asy.c \
../Sources/MCU_DRIVERS/ASY/io_bluetooth.c \
../Sources/MCU_DRIVERS/ASY/io_cnfasy.c 

OBJS += \
./Sources/MCU_DRIVERS/ASY/io_asy.o \
./Sources/MCU_DRIVERS/ASY/io_bluetooth.o \
./Sources/MCU_DRIVERS/ASY/io_cnfasy.o 

C_DEPS += \
./Sources/MCU_DRIVERS/ASY/io_asy.d \
./Sources/MCU_DRIVERS/ASY/io_bluetooth.d \
./Sources/MCU_DRIVERS/ASY/io_cnfasy.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU_DRIVERS/ASY/%.o: ../Sources/MCU_DRIVERS/ASY/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


