################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/APPLICATION/ALGO/CAR_MOVEMENT/app_robo_car_movement.c 

OBJS += \
./Sources/APPLICATION/ALGO/CAR_MOVEMENT/app_robo_car_movement.o 

C_DEPS += \
./Sources/APPLICATION/ALGO/CAR_MOVEMENT/app_robo_car_movement.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/APPLICATION/ALGO/CAR_MOVEMENT/%.o: ../Sources/APPLICATION/ALGO/CAR_MOVEMENT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


