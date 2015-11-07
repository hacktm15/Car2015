################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/HW_INTERFACES/H_BRIDGE/io_hbr_cnf.c \
../Sources/HW_INTERFACES/H_BRIDGE/io_hbr_main.c 

OBJS += \
./Sources/HW_INTERFACES/H_BRIDGE/io_hbr_cnf.o \
./Sources/HW_INTERFACES/H_BRIDGE/io_hbr_main.o 

C_DEPS += \
./Sources/HW_INTERFACES/H_BRIDGE/io_hbr_cnf.d \
./Sources/HW_INTERFACES/H_BRIDGE/io_hbr_main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/HW_INTERFACES/H_BRIDGE/%.o: ../Sources/HW_INTERFACES/H_BRIDGE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


