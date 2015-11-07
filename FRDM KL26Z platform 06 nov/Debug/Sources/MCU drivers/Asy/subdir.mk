################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU\ drivers/Asy/io_asy.c \
../Sources/MCU\ drivers/Asy/io_asy_cnf.c 

OBJS += \
./Sources/MCU\ drivers/Asy/io_asy.o \
./Sources/MCU\ drivers/Asy/io_asy_cnf.o 

C_DEPS += \
./Sources/MCU\ drivers/Asy/io_asy.d \
./Sources/MCU\ drivers/Asy/io_asy_cnf.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU\ drivers/Asy/io_asy.o: ../Sources/MCU\ drivers/Asy/io_asy.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Asy/io_asy.d" -MT"Sources/MCU\ drivers/Asy/io_asy.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/MCU\ drivers/Asy/io_asy_cnf.o: ../Sources/MCU\ drivers/Asy/io_asy_cnf.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Asy/io_asy_cnf.d" -MT"Sources/MCU\ drivers/Asy/io_asy_cnf.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


