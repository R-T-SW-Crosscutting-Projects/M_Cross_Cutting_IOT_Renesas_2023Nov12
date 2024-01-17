################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/MCAL/UART/MCAL_R5F11BBC_UART.c 

COMPILER_OBJS += \
src/MCAL/UART/MCAL_R5F11BBC_UART.obj 

C_DEPS += \
src/MCAL/UART/MCAL_R5F11BBC_UART.d 

# Each subdirectory must supply rules for building sources it contributes
src/MCAL/UART/%.obj: ../src/MCAL/UART/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\MCAL\UART\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\MCAL\UART\cDepSubCommand.tmp"
	ccrl -subcommand="src\MCAL\UART\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\MCAL\UART\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\MCAL\UART\cSubCommand.tmp"
	ccrl -subcommand="src\MCAL\UART\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

