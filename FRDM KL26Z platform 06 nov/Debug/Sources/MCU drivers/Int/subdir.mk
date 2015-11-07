################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU\ drivers/Int/io_int.c \
../Sources/MCU\ drivers/Int/io_int_cnf.c 

OBJS += \
./Sources/MCU\ drivers/Int/io_int.o \
./Sources/MCU\ drivers/Int/io_int_cnf.o 

C_DEPS += \
./Sources/MCU\ drivers/Int/io_int.d \
./Sources/MCU\ drivers/Int/io_int_cnf.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU\ drivers/Int/io_int.o: ../Sources/MCU\ drivers/Int/io_int.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Int/io_int.d" -MT"Sources/MCU\ drivers/Int/io_int.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/MCU\ drivers/Int/io_int_cnf.o: ../Sources/MCU\ drivers/Int/io_int_cnf.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Int/io_int_cnf.d" -MT"Sources/MCU\ drivers/Int/io_int_cnf.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


