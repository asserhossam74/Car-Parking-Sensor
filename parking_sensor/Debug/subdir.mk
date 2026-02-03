################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
../gpio.c \
../icu.c \
../lcd.c \
../led.c \
../parking_sensor.c \
../ultrasonic_sensor.c 

OBJS += \
./buzzer.o \
./gpio.o \
./icu.o \
./lcd.o \
./led.o \
./parking_sensor.o \
./ultrasonic_sensor.o 

C_DEPS += \
./buzzer.d \
./gpio.d \
./icu.d \
./lcd.d \
./led.d \
./parking_sensor.d \
./ultrasonic_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


