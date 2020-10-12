################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third_party/FreeRTOS/ORG/Source/portable/MemMang/heap_4.c 

OBJS += \
./Third_party/FreeRTOS/ORG/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Third_party/FreeRTOS/ORG/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Third_party/FreeRTOS/ORG/Source/portable/MemMang/%.o: ../Third_party/FreeRTOS/ORG/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"D:/PENDRIVE/EMBEDDED_SYSTEM/STM32_PROJECTS/FreeRTOS_Project/FreeRTOS_Simple_Task/FreeRTOS_Simple_Task/StdPeriph_Driver/inc" -I"D:/PENDRIVE/EMBEDDED_SYSTEM/STM32_PROJECTS/FreeRTOS_Project/FreeRTOS_Simple_Task/FreeRTOS_Simple_Task/Third_party/FreeRTOS/ORG/Source/include" -I"D:/PENDRIVE/EMBEDDED_SYSTEM/STM32_PROJECTS/FreeRTOS_Project/FreeRTOS_Simple_Task/FreeRTOS_Simple_Task/Third_party/FreeRTOS/ORG/Source/portable/GCC/ARM_CM4F" -I"D:/PENDRIVE/EMBEDDED_SYSTEM/STM32_PROJECTS/FreeRTOS_Project/FreeRTOS_Simple_Task/FreeRTOS_Simple_Task/Config" -I"D:/PENDRIVE/EMBEDDED_SYSTEM/STM32_PROJECTS/FreeRTOS_Project/FreeRTOS_Simple_Task/FreeRTOS_Simple_Task/inc" -I"D:/PENDRIVE/EMBEDDED_SYSTEM/STM32_PROJECTS/FreeRTOS_Project/FreeRTOS_Simple_Task/FreeRTOS_Simple_Task/CMSIS/device" -I"D:/PENDRIVE/EMBEDDED_SYSTEM/STM32_PROJECTS/FreeRTOS_Project/FreeRTOS_Simple_Task/FreeRTOS_Simple_Task/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


