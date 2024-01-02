################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.h *.bls *.libelf *.rel *.lbk *.abs *.prn *.mi *.fsy *.ud *.udm 1st/*.abs 1st/*.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/MIDDLEWARE/subdir.mk
-include generate/subdir.mk
-include src/MCAL/GPIO/subdir.mk
-include src/MCAL/INTERVALTIMER/subdir.mk
-include src/HAL/IOT/subdir.mk
-include src/MCAL/subdir.mk
-include src/OS/subdir.mk
-include src/HAL/PB/subdir.mk
-include src/MCAL/UART/subdir.mk
-include src/HAL/SSD/subdir.mk
-include src/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
IOT_phase_2.abs

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)


# All Target
all: $(LINKER_OUTPUT_OUTPUTS) IOT_phase_2.x IOT_phase_2.udm

	@echo 'Build complete.'

IOT_phase_2.abs: $(OBJS)  $(ALL_ASMS)
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	@echo LinkerIOT_phase_2.tmp=
	@sed -e "s/^/    /" "LinkerIOT_phase_2.tmp"
	rlink -subcommand="LinkerIOT_phase_2.tmp"
	@echo 'Finished building target:'
	@echo ''


IOT_phase_2.x: IOT_phase_2.abs
		-D:\ELARABY\e2_Work_Space\.eclipse\com.renesas.platform_1435879475\Utilities\\ccrl\renesas_cc_converter IOT_phase_2.abs IOT_phase_2.x

IOT_phase_2.udm: $(LINKER_OUTPUT_OUTPUTS)
	udcollector -subcommand=udSubcommand.tmp -output=IOT_phase_2.udm

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS)
ifneq ($(strip $(OBJS)),)
	-$(file > clean_OBJS.tmp, $(OBJS))
	-@xargs -s 4000 -t -a clean_OBJS.tmp rm -rf
	-@rm -rf clean_OBJS.tmp
endif
ifneq ($(strip $(C_DEPS)),)
	-$(file > clean_C_DEPS.tmp, $(C_DEPS))
	-@xargs -s 4000 -t -a clean_C_DEPS.tmp rm -rf
	-@rm -rf clean_C_DEPS.tmp
endif
ifneq ($(strip $(CPP_DEPS)),)
	-$(file > clean_CPP_DEPS.tmp, $(CPP_DEPS))
	-@xargs -s 4000 -t -a clean_CPP_DEPS.tmp rm -rf
	-@rm -rf clean_CPP_DEPS.tmp
endif
ifneq ($(strip $(ASM_DEPS)),)
	-$(file > clean_ASM_DEPS.tmp, $(ASM_DEPS))
	-@xargs -s 4000 -t -a clean_ASM_DEPS.tmp rm -rf
	-@rm -rf clean_ASM_DEPS.tmp
endif
ifneq ($(strip $(DSP_DEPS)),)
	-$(file > clean_DSP_DEPS.tmp, $(DSP_DEPS))
	-@xargs -s 4000 -t -a clean_DSP_DEPS.tmp rm -rf
	-@rm -rf clean_DSP_DEPS.tmp
endif
	-rm -rf src/MIDDLEWARE/*.asm src/MIDDLEWARE/*.p src/MIDDLEWARE/*.pp src/MIDDLEWARE/*.src src/MIDDLEWARE/*.jmp src/MIDDLEWARE/*.lst src/MIDDLEWARE/*.prn src/MIDDLEWARE/*.i src/MIDDLEWARE/*.ud 
	-rm -rf generate/*.asm generate/*.p generate/*.pp generate/*.src generate/*.jmp generate/*.lst generate/*.prn generate/*.i generate/*.ud 
	-rm -rf src/MCAL/GPIO/*.asm src/MCAL/GPIO/*.p src/MCAL/GPIO/*.pp src/MCAL/GPIO/*.src src/MCAL/GPIO/*.jmp src/MCAL/GPIO/*.lst src/MCAL/GPIO/*.prn src/MCAL/GPIO/*.i src/MCAL/GPIO/*.ud 
	-rm -rf src/MCAL/INTERVALTIMER/*.asm src/MCAL/INTERVALTIMER/*.p src/MCAL/INTERVALTIMER/*.pp src/MCAL/INTERVALTIMER/*.src src/MCAL/INTERVALTIMER/*.jmp src/MCAL/INTERVALTIMER/*.lst src/MCAL/INTERVALTIMER/*.prn src/MCAL/INTERVALTIMER/*.i src/MCAL/INTERVALTIMER/*.ud 
	-rm -rf src/HAL/IOT/*.asm src/HAL/IOT/*.p src/HAL/IOT/*.pp src/HAL/IOT/*.src src/HAL/IOT/*.jmp src/HAL/IOT/*.lst src/HAL/IOT/*.prn src/HAL/IOT/*.i src/HAL/IOT/*.ud 
	-rm -rf src/MCAL/*.asm src/MCAL/*.p src/MCAL/*.pp src/MCAL/*.src src/MCAL/*.jmp src/MCAL/*.lst src/MCAL/*.prn src/MCAL/*.i src/MCAL/*.ud 
	-rm -rf src/OS/*.asm src/OS/*.p src/OS/*.pp src/OS/*.src src/OS/*.jmp src/OS/*.lst src/OS/*.prn src/OS/*.i src/OS/*.ud 
	-rm -rf src/HAL/PB/*.asm src/HAL/PB/*.p src/HAL/PB/*.pp src/HAL/PB/*.src src/HAL/PB/*.jmp src/HAL/PB/*.lst src/HAL/PB/*.prn src/HAL/PB/*.i src/HAL/PB/*.ud 
	-rm -rf src/MCAL/UART/*.asm src/MCAL/UART/*.p src/MCAL/UART/*.pp src/MCAL/UART/*.src src/MCAL/UART/*.jmp src/MCAL/UART/*.lst src/MCAL/UART/*.prn src/MCAL/UART/*.i src/MCAL/UART/*.ud 
	-rm -rf src/HAL/SSD/*.asm src/HAL/SSD/*.p src/HAL/SSD/*.pp src/HAL/SSD/*.src src/HAL/SSD/*.jmp src/HAL/SSD/*.lst src/HAL/SSD/*.prn src/HAL/SSD/*.i src/HAL/SSD/*.ud 
	-rm -rf src/*.asm src/*.p src/*.pp src/*.src src/*.jmp src/*.lst src/*.prn src/*.i src/*.ud 
	@echo ''
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets