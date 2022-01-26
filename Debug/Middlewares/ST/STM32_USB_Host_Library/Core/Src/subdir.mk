################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c 

OBJS += \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.o: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ak4343 -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/cs43l22 -I../Drivers/BSP/Components/hx8347d -I../Drivers/BSP/Components/ili9320 -I../Drivers/BSP/Components/ili9325 -I../Drivers/BSP/Components/lis302dl -I../Drivers/BSP/Components/spfd5408 -I../Drivers/BSP/Components/st7735 -I../Drivers/BSP/Components/stlm75 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/BSP/STM3210C_EVAL -I../Utilities/CPU -I../Utilities/Fonts -I../Utilities/Log -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ak4343 -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/cs43l22 -I../Drivers/BSP/Components/hx8347d -I../Drivers/BSP/Components/ili9320 -I../Drivers/BSP/Components/ili9325 -I../Drivers/BSP/Components/lis302dl -I../Drivers/BSP/Components/spfd5408 -I../Drivers/BSP/Components/st7735 -I../Drivers/BSP/Components/stlm75 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/BSP/STM3210C_EVAL -I../Utilities/CPU -I../Utilities/Fonts -I../Utilities/Log -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ak4343 -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/cs43l22 -I../Drivers/BSP/Components/hx8347d -I../Drivers/BSP/Components/ili9320 -I../Drivers/BSP/Components/ili9325 -I../Drivers/BSP/Components/lis302dl -I../Drivers/BSP/Components/spfd5408 -I../Drivers/BSP/Components/st7735 -I../Drivers/BSP/Components/stlm75 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/BSP/STM3210C_EVAL -I../Utilities/CPU -I../Utilities/Fonts -I../Utilities/Log -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.o: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ak4343 -I../Drivers/BSP/Components/Common -I../Drivers/BSP/Components/cs43l22 -I../Drivers/BSP/Components/hx8347d -I../Drivers/BSP/Components/ili9320 -I../Drivers/BSP/Components/ili9325 -I../Drivers/BSP/Components/lis302dl -I../Drivers/BSP/Components/spfd5408 -I../Drivers/BSP/Components/st7735 -I../Drivers/BSP/Components/stlm75 -I../Drivers/BSP/Components/stmpe811 -I../Drivers/BSP/STM3210C_EVAL -I../Utilities/CPU -I../Utilities/Fonts -I../Utilities/Log -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

