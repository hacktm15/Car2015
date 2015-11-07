################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Sources/TEST_FUNCTIONS/subdir.mk
-include Sources/SYSTEM/SCHEDULER/subdir.mk
-include Sources/SYSTEM/OS/subdir.mk
-include Sources/SYSTEM/ERROR_HANDLING/subdir.mk
-include Sources/OTHER_FUNCTIONS/subdir.mk
-include Sources/MCU_DRIVERS/TPM/subdir.mk
-include Sources/MCU_DRIVERS/TIMER/subdir.mk
-include Sources/MCU_DRIVERS/PCS/subdir.mk
-include Sources/MCU_DRIVERS/INT/subdir.mk
-include Sources/MCU_DRIVERS/DIO/subdir.mk
-include Sources/MCU_DRIVERS/ASY/subdir.mk
-include Sources/MCU_DRIVERS/ADC/subdir.mk
-include Sources/HW_INTERFACES/STEPPER_MOTOR/subdir.mk
-include Sources/HW_INTERFACES/SENSORS/subdir.mk
-include Sources/HW_INTERFACES/H_BRIDGE/subdir.mk
-include Sources/APPLICATION/ALGO/SPEED_CALC/subdir.mk
-include Sources/APPLICATION/ALGO/PATH_PLANNER/subdir.mk
-include Sources/APPLICATION/ALGO/DISTANCE_CALC/subdir.mk
-include Sources/APPLICATION/ALGO/CAR_MOVEMENT/subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: KL26_Conti_test.elf secondary-outputs

# Tool invocations
KL26_Conti_test.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "MKL26Z128xxx4_flash.ld" -Xlinker --gc-sections -L"C:/Users/UIDK9029/Documents/SametimeFileTransfers/KL26_Conti_Autonomous Car 2015-2/KL26_Conti_test/Project_Settings/Linker_Files" -Wl,-Map,"KL26_Conti_test.map" -specs=nano.specs -specs=nosys.specs -o "KL26_Conti_test.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) KL26_Conti_test.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
