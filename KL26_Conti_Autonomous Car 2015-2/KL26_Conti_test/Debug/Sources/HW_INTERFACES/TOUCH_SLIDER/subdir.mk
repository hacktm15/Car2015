################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/HW_INTERFACES/TOUCH_SLIDER/TSIDrv.c 

OBJS += \
./Sources/HW_INTERFACES/TOUCH_SLIDER/TSIDrv.o 

C_DEPS += \
./Sources/HW_INTERFACES/TOUCH_SLIDER/TSIDrv.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/HW_INTERFACES/TOUCH_SLIDER/%.o: ../Sources/HW_INTERFACES/TOUCH_SLIDER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


