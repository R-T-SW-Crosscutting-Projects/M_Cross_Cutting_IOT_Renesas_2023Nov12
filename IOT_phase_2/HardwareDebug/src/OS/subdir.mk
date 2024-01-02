################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/OS/tt_scheduler.c 

COMPILER_OBJS += \
src/OS/tt_scheduler.obj 

C_DEPS += \
src/OS/tt_scheduler.d 

# Each subdirectory must supply rules for building sources it contributes
src/OS/%.obj: ../src/OS/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\OS\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\OS\cDepSubCommand.tmp"
	ccrl -subcommand="src\OS\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\OS\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\OS\cSubCommand.tmp"
	ccrl -subcommand="src\OS\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

