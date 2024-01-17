################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/MCAL/MCAL_R5F11BBC_Config.c 

COMPILER_OBJS += \
src/MCAL/MCAL_R5F11BBC_Config.obj 

C_DEPS += \
src/MCAL/MCAL_R5F11BBC_Config.d 

# Each subdirectory must supply rules for building sources it contributes
src/MCAL/%.obj: ../src/MCAL/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\MCAL\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\MCAL\cDepSubCommand.tmp"
	ccrl -subcommand="src\MCAL\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\MCAL\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\MCAL\cSubCommand.tmp"
	ccrl -subcommand="src\MCAL\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

