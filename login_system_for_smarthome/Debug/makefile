################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/WDT/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIMER0/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/INT/subdir.mk
-include MCAL/ICU/subdir.mk
-include MCAL/I2C/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/Stepper_Motor/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include HAL/EEPROM/subdir.mk
-include APP/SSD/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
login_system_for_smarthome.lss \

FLASH_IMAGE += \
login_system_for_smarthome.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: login_system_for_smarthome.elf secondary-outputs

# Tool invocations
login_system_for_smarthome.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,login_system_for_smarthome.map -mmcu=atmega32 -o "login_system_for_smarthome.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

login_system_for_smarthome.lss: login_system_for_smarthome.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S login_system_for_smarthome.elf  >"login_system_for_smarthome.lss"
	@echo 'Finished building: $@'
	@echo ' '

login_system_for_smarthome.hex: login_system_for_smarthome.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex login_system_for_smarthome.elf  "login_system_for_smarthome.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: login_system_for_smarthome.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 login_system_for_smarthome.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) login_system_for_smarthome.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
