################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/System/Scheduler/io_sch.c \
../Sources/System/Scheduler/io_sch_cnf.c 

OBJS += \
./Sources/System/Scheduler/io_sch.o \
./Sources/System/Scheduler/io_sch_cnf.o 

C_DEPS += \
./Sources/System/Scheduler/io_sch.d \
./Sources/System/Scheduler/io_sch_cnf.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/System/Scheduler/%.o: ../Sources/System/Scheduler/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -I"../Sources" -I"../Includes" -std=c99 -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


