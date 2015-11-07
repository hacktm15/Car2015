################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/MCU\ drivers/Tpm/io_tpm.c \
../Sources/MCU\ drivers/Tpm/io_tpm_cnf.c 

OBJS += \
./Sources/MCU\ drivers/Tpm/io_tpm.o \
./Sources/MCU\ drivers/Tpm/io_tpm_cnf.o 

C_DEPS += \
./Sources/MCU\ drivers/Tpm/io_tpm.d \
./Sources/MCU\ drivers/Tpm/io_tpm_cnf.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/MCU\ drivers/Tpm/io_tpm.o: ../Sources/MCU\ drivers/Tpm/io_tpm.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Tpm/io_tpm.d" -MT"Sources/MCU\ drivers/Tpm/io_tpm.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/MCU\ drivers/Tpm/io_tpm_cnf.o: ../Sources/MCU\ drivers/Tpm/io_tpm_cnf.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/MCU drivers/Tpm/io_tpm_cnf.d" -MT"Sources/MCU\ drivers/Tpm/io_tpm_cnf.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


