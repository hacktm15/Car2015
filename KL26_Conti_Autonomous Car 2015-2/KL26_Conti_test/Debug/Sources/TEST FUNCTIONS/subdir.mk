################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/TEST\ FUNCTIONS/io_adc_test.c \
../Sources/TEST\ FUNCTIONS/io_tpm_test.c 

OBJS += \
./Sources/TEST\ FUNCTIONS/io_adc_test.o \
./Sources/TEST\ FUNCTIONS/io_tpm_test.o 

C_DEPS += \
./Sources/TEST\ FUNCTIONS/io_adc_test.d \
./Sources/TEST\ FUNCTIONS/io_tpm_test.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/TEST\ FUNCTIONS/io_adc_test.o: ../Sources/TEST\ FUNCTIONS/io_adc_test.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/TEST FUNCTIONS/io_adc_test.d" -MT"Sources/TEST\ FUNCTIONS/io_adc_test.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TEST\ FUNCTIONS/io_tpm_test.o: ../Sources/TEST\ FUNCTIONS/io_tpm_test.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"Sources/TEST FUNCTIONS/io_tpm_test.d" -MT"Sources/TEST\ FUNCTIONS/io_tpm_test.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


