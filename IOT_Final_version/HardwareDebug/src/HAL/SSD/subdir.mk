################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/HAL/SSD/Component_SSD.c 

COMPILER_OBJS += \
src/HAL/SSD/Component_SSD.obj 

C_DEPS += \
src/HAL/SSD/Component_SSD.d 

# Each subdirectory must supply rules for building sources it contributes
src/HAL/SSD/%.obj: ../src/HAL/SSD/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\HAL\SSD\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\HAL\SSD\cDepSubCommand.tmp"
	ccrl -subcommand="src\HAL\SSD\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\HAL\SSD\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\HAL\SSD\cSubCommand.tmp"
	ccrl -subcommand="src\HAL\SSD\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

