################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MATH/math.c 

C_DEPS += \
./Drivers/MATH/math.d 

OBJS += \
./Drivers/MATH/math.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MATH/%.o Drivers/MATH/%.su Drivers/MATH/%.cyclo: ../Drivers/MATH/%.c Drivers/MATH/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-MATH

clean-Drivers-2f-MATH:
	-$(RM) ./Drivers/MATH/math.cyclo ./Drivers/MATH/math.d ./Drivers/MATH/math.o ./Drivers/MATH/math.su

.PHONY: clean-Drivers-2f-MATH

