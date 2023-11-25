################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/MCAL/INTERVALTIMER/Interval_Timer.c 

COMPILER_OBJS += \
src/MCAL/INTERVALTIMER/Interval_Timer.obj 

C_DEPS += \
src/MCAL/INTERVALTIMER/Interval_Timer.d 

# Each subdirectory must supply rules for building sources it contributes
src/MCAL/INTERVALTIMER/%.obj: ../src/MCAL/INTERVALTIMER/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\MCAL\INTERVALTIMER\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\MCAL\INTERVALTIMER\cDepSubCommand.tmp"
	ccrl -subcommand="src\MCAL\INTERVALTIMER\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\MCAL\INTERVALTIMER\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\MCAL\INTERVALTIMER\cSubCommand.tmp"
	ccrl -subcommand="src\MCAL\INTERVALTIMER\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)"  "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

