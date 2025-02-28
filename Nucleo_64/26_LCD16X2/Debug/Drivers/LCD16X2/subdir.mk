################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LCD16X2/LCD16X2.c \
../Drivers/LCD16X2/LCD16X2_cfg.c 

C_DEPS += \
./Drivers/LCD16X2/LCD16X2.d \
./Drivers/LCD16X2/LCD16X2_cfg.d 

OBJS += \
./Drivers/LCD16X2/LCD16X2.o \
./Drivers/LCD16X2/LCD16X2_cfg.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LCD16X2/%.o Drivers/LCD16X2/%.su Drivers/LCD16X2/%.cyclo: ../Drivers/LCD16X2/%.c Drivers/LCD16X2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-LCD16X2

clean-Drivers-2f-LCD16X2:
	-$(RM) ./Drivers/LCD16X2/LCD16X2.cyclo ./Drivers/LCD16X2/LCD16X2.d ./Drivers/LCD16X2/LCD16X2.o ./Drivers/LCD16X2/LCD16X2.su ./Drivers/LCD16X2/LCD16X2_cfg.cyclo ./Drivers/LCD16X2/LCD16X2_cfg.d ./Drivers/LCD16X2/LCD16X2_cfg.o ./Drivers/LCD16X2/LCD16X2_cfg.su

.PHONY: clean-Drivers-2f-LCD16X2

