################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/TEST_FUNCTIONS/io_adc_test.c \
../Sources/TEST_FUNCTIONS/io_tpm_test.c 

OBJS += \
./Sources/TEST_FUNCTIONS/io_adc_test.o \
./Sources/TEST_FUNCTIONS/io_tpm_test.o 

C_DEPS += \
./Sources/TEST_FUNCTIONS/io_adc_test.d \
./Sources/TEST_FUNCTIONS/io_tpm_test.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/TEST_FUNCTIONS/%.o: ../Sources/TEST_FUNCTIONS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


