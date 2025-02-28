################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Util/Util.c 

C_DEPS += \
./Drivers/Util/Util.d 

OBJS += \
./Drivers/Util/Util.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Util/%.o Drivers/Util/%.su Drivers/Util/%.cyclo: ../Drivers/Util/%.c Drivers/Util/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Util

clean-Drivers-2f-Util:
	-$(RM) ./Drivers/Util/Util.cyclo ./Drivers/Util/Util.d ./Drivers/Util/Util.o ./Drivers/Util/Util.su

.PHONY: clean-Drivers-2f-Util

