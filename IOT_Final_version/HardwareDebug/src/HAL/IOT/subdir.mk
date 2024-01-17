################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/HAL/IOT/iot.c 

COMPILER_OBJS += \
src/HAL/IOT/iot.obj 

C_DEPS += \
src/HAL/IOT/iot.d 

# Each subdirectory must supply rules for building sources it contributes
src/HAL/IOT/%.obj: ../src/HAL/IOT/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\HAL\IOT\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\HAL\IOT\cDepSubCommand.tmp"
	ccrl -subcommand="src\HAL\IOT\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\HAL\IOT\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\HAL\IOT\cSubCommand.tmp"
	ccrl -subcommand="src\HAL\IOT\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

