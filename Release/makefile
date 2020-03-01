################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
GSM_GPRS_Module_Nmr.lss \

FLASH_IMAGE += \
GSM_GPRS_Module_Nmr.hex \

EEPROM_IMAGE += \
GSM_GPRS_Module_Nmr.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: GSM_GPRS_Module_Nmr.elf secondary-outputs

# Tool invocations
GSM_GPRS_Module_Nmr.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,GSM_GPRS_Module_Nmr.map -mmcu=atmega32 -o "GSM_GPRS_Module_Nmr.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

GSM_GPRS_Module_Nmr.lss: GSM_GPRS_Module_Nmr.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S GSM_GPRS_Module_Nmr.elf  >"GSM_GPRS_Module_Nmr.lss"
	@echo 'Finished building: $@'
	@echo ' '

GSM_GPRS_Module_Nmr.hex: GSM_GPRS_Module_Nmr.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex GSM_GPRS_Module_Nmr.elf  "GSM_GPRS_Module_Nmr.hex"
	@echo 'Finished building: $@'
	@echo ' '

GSM_GPRS_Module_Nmr.eep: GSM_GPRS_Module_Nmr.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex GSM_GPRS_Module_Nmr.elf  "GSM_GPRS_Module_Nmr.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: GSM_GPRS_Module_Nmr.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 GSM_GPRS_Module_Nmr.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) GSM_GPRS_Module_Nmr.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
