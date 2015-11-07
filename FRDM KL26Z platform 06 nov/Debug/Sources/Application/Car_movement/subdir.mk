################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Application/Car_movement/app_robo_car_movement.c 

OBJS += \
./Sources/Application/Car_movement/app_robo_car_movement.o 

C_DEPS += \
./Sources/Application/Car_movement/app_robo_car_movement.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Car_movement/%.o: ../Sources/Application/Car_movement/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"../Sources" -I"../Includes" -std=c99 -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


