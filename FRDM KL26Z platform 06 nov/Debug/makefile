################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Sources/System/Scheduler/subdir.mk
-include Sources/System/Os/subdir.mk
-include Sources/System/Error_handling/subdir.mk
-include Sources/Other_functions/subdir.mk
-include Sources/MCU_drivers/Wdt/subdir.mk
-include Sources/MCU_drivers/Tpm/subdir.mk
-include Sources/MCU_drivers/Timer/subdir.mk
-include Sources/MCU_drivers/Pcs/subdir.mk
-include Sources/MCU_drivers/Int/subdir.mk
-include Sources/MCU_drivers/I2c/subdir.mk
-include Sources/MCU_drivers/Dio/subdir.mk
-include Sources/MCU_drivers/Asy/subdir.mk
-include Sources/MCU_drivers/Adc/subdir.mk
-include Sources/HW_drivers/Stepper_motor/subdir.mk
-include Sources/HW_drivers/Sensors/Proximity/subdir.mk
-include Sources/HW_drivers/Sensors/Accel_Magnet/subdir.mk
-include Sources/HW_drivers/H-bridge/ti8833/subdir.mk
-include Sources/Application/Speed_calc/subdir.mk
-include Sources/Application/Path_planner/subdir.mk
-include Sources/Application/Distance_calc/subdir.mk
-include Sources/Application/Car_movement/subdir.mk
-include Sources/Application/Bluetooth/subdir.mk
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
all: FRDM\ KL26Z\ platform.elf secondary-outputs

# Tool invocations
FRDM\ KL26Z\ platform.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -T "MKL26Z128xxx4_flash.ld" -Xlinker --gc-sections -L"C:/Users/Gabi/Desktop/HackTM/FRDM KL26Z platform 06 nov/Project_Settings/Linker_Files" -Wl,-Map,"FRDM KL26Z platform.map" -specs=nano.specs -specs=nosys.specs -o "FRDM KL26Z platform.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) "FRDM KL26Z platform.elf"
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
