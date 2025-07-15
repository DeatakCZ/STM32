################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LM35/LM35.c \
../Drivers/LM35/LM35_cfg.c 

C_DEPS += \
./Drivers/LM35/LM35.d \
./Drivers/LM35/LM35_cfg.d 

OBJS += \
./Drivers/LM35/LM35.o \
./Drivers/LM35/LM35_cfg.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LM35/%.o Drivers/LM35/%.su Drivers/LM35/%.cyclo: ../Drivers/LM35/%.c Drivers/LM35/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G050xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-LM35

clean-Drivers-2f-LM35:
	-$(RM) ./Drivers/LM35/LM35.cyclo ./Drivers/LM35/LM35.d ./Drivers/LM35/LM35.o ./Drivers/LM35/LM35.su ./Drivers/LM35/LM35_cfg.cyclo ./Drivers/LM35/LM35_cfg.d ./Drivers/LM35/LM35_cfg.o ./Drivers/LM35/LM35_cfg.su

.PHONY: clean-Drivers-2f-LM35

