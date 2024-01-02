################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/HAL/PB/Component_PB.c 

COMPILER_OBJS += \
src/HAL/PB/Component_PB.obj 

C_DEPS += \
src/HAL/PB/Component_PB.d 

# Each subdirectory must supply rules for building sources it contributes
src/HAL/PB/%.obj: ../src/HAL/PB/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\HAL\PB\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\HAL\PB\cDepSubCommand.tmp"
	ccrl -subcommand="src\HAL\PB\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\HAL\PB\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\HAL\PB\cSubCommand.tmp"
	ccrl -subcommand="src\HAL\PB\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

