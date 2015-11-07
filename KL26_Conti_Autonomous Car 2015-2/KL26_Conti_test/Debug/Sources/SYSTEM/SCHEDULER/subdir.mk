################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/SYSTEM/SCHEDULER/io_sch_cnf.c \
../Sources/SYSTEM/SCHEDULER/io_sch_main.c 

OBJS += \
./Sources/SYSTEM/SCHEDULER/io_sch_cnf.o \
./Sources/SYSTEM/SCHEDULER/io_sch_main.o 

C_DEPS += \
./Sources/SYSTEM/SCHEDULER/io_sch_cnf.d \
./Sources/SYSTEM/SCHEDULER/io_sch_main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/SYSTEM/SCHEDULER/%.o: ../Sources/SYSTEM/SCHEDULER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


