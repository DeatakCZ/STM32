################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Util/DWT_Delay.c \
../Core/Src/Util/Timer_Delay.c 

C_DEPS += \
./Core/Src/Util/DWT_Delay.d \
./Core/Src/Util/Timer_Delay.d 

OBJS += \
./Core/Src/Util/DWT_Delay.o \
./Core/Src/Util/Timer_Delay.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Util/%.o Core/Src/Util/%.su Core/Src/Util/%.cyclo: ../Core/Src/Util/%.c Core/Src/Util/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Util

clean-Core-2f-Src-2f-Util:
	-$(RM) ./Core/Src/Util/DWT_Delay.cyclo ./Core/Src/Util/DWT_Delay.d ./Core/Src/Util/DWT_Delay.o ./Core/Src/Util/DWT_Delay.su ./Core/Src/Util/Timer_Delay.cyclo ./Core/Src/Util/Timer_Delay.d ./Core/Src/Util/Timer_Delay.o ./Core/Src/Util/Timer_Delay.su

.PHONY: clean-Core-2f-Src-2f-Util

