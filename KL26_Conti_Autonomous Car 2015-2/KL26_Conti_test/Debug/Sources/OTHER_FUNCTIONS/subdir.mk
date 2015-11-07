################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/OTHER_FUNCTIONS/io_func_main.c 

OBJS += \
./Sources/OTHER_FUNCTIONS/io_func_main.o 

C_DEPS += \
./Sources/OTHER_FUNCTIONS/io_func_main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/OTHER_FUNCTIONS/%.o: ../Sources/OTHER_FUNCTIONS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


