################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/INTERRUPTS/io_int_cnf.c \
../Sources/INTERRUPTS/io_int_main.c 

OBJS += \
./Sources/INTERRUPTS/io_int_cnf.o \
./Sources/INTERRUPTS/io_int_main.o 

C_DEPS += \
./Sources/INTERRUPTS/io_int_cnf.d \
./Sources/INTERRUPTS/io_int_main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/INTERRUPTS/%.o: ../Sources/INTERRUPTS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


