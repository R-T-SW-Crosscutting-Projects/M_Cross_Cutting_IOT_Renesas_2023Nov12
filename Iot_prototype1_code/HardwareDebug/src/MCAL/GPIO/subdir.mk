################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/MCAL/GPIO/MCAL_R5F11BBC_GPIO.c 

COMPILER_OBJS += \
src/MCAL/GPIO/MCAL_R5F11BBC_GPIO.obj 

C_DEPS += \
src/MCAL/GPIO/MCAL_R5F11BBC_GPIO.d 

# Each subdirectory must supply rules for building sources it contributes
src/MCAL/GPIO/%.obj: ../src/MCAL/GPIO/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\MCAL\GPIO\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\MCAL\GPIO\cDepSubCommand.tmp"
	ccrl -subcommand="src\MCAL\GPIO\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\MCAL\GPIO\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\MCAL\GPIO\cSubCommand.tmp"
	ccrl -subcommand="src\MCAL\GPIO\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

