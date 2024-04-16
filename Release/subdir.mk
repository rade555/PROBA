################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../input_event.c \
../keypad.c \
../main.c \
../output_event.c \
../pin.c \
../timer0.c \
../usart.c 

OBJS += \
./input_event.o \
./keypad.o \
./main.o \
./output_event.o \
./pin.o \
./timer0.o \
./usart.o 

C_DEPS += \
./input_event.d \
./keypad.d \
./main.d \
./output_event.d \
./pin.d \
./timer0.d \
./usart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


