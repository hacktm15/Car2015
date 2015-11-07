################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/SYSTEM/OS/io_os_main.c 

OBJS += \
./Sources/SYSTEM/OS/io_os_main.o 

C_DEPS += \
./Sources/SYSTEM/OS/io_os_main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/SYSTEM/OS/%.o: ../Sources/SYSTEM/OS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


