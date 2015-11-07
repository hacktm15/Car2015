################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Application/Autonomous_car_2015/Speed_calc/app_robo_speed_calc.c 

OBJS += \
./Sources/Application/Autonomous_car_2015/Speed_calc/app_robo_speed_calc.o 

C_DEPS += \
./Sources/Application/Autonomous_car_2015/Speed_calc/app_robo_speed_calc.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Autonomous_car_2015/Speed_calc/%.o: ../Sources/Application/Autonomous_car_2015/Speed_calc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"../Sources" -I"../Includes" -std=c99 -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


