################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/MIDDLEWARE/Middleware.c 

COMPILER_OBJS += \
src/MIDDLEWARE/Middleware.obj 

C_DEPS += \
src/MIDDLEWARE/Middleware.d 

# Each subdirectory must supply rules for building sources it contributes
src/MIDDLEWARE/%.obj: ../src/MIDDLEWARE/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\MIDDLEWARE\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\MIDDLEWARE\cDepSubCommand.tmp"
	ccrl -subcommand="src\MIDDLEWARE\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\MIDDLEWARE\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\MIDDLEWARE\cSubCommand.tmp"
	ccrl -subcommand="src\MIDDLEWARE\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''

