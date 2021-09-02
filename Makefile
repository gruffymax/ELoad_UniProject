# Makefile for Electronic Load Project
# Written by Gareth Waymark
# @ stops the command echo

LINK_TARGET := ElectronicLoad

INCS := -IInc \
        -IInc/Hardware \
        -IInc/Tasks \
        -IDrivers/CMSIS/Include \
        -IDrivers/CMSIS/Device/ST/STM32G0xx/Include \
        -IFreeRTOS/Source/include \
        -IFreeRTOS/Source/portable/GCC/ARM_CM0

SRCS := $(wildcard Src/*.c) \
        $(wildcard Src/Hardware/*.c) \
        $(wildcard Src/Tasks/*.c) \
        Startup/startup_stm32g071xx.o \
        $(wildcard FreeRTOS/Source/*.c) \
        FreeRTOS/Source/portable/MemMang/heap_4.o \
        FreeRTOS/Source/portable/GCC/ARM_CM0/port.o

OBJS := $(SRCS:.c=.o)
CFLAGS := \
     -DSTM32G071xx \
     -mcpu=cortex-m0plus \
     -g3 \
     -O0 \
     -ffunction-sections \
     -fdata-sections \
     -Wall \
     --specs=nano.specs \
     -mfloat-abi=soft \
     -mthumb \
     -c

LFLAGS=\
     -T/home/gareth/Uni/L6/Individual_Project/STM32/STM32G071CBTx_FLASH.ld \
     -mcpu=cortex-m0plus \
     -mthumb \
     -mfloat-abi=soft \
     --specs=nosys.specs \
     --specs=nano.specs \
     -Wl,-Map=ElectronicLoad.map \
     -Wl,--gc-sections \
     -static

OUTPUT=@echo -e "\e[1;36m$@\e[1;m"

BUILD_DIR=build/



all: $(LINK_TARGET).elf hex size

.PHONY: debug
debug:
	@echo $(OBJS)

$(LINK_TARGET).elf: $(OBJS)
	@arm-none-eabi-gcc $(LFLAGS) $(INCS) -o $@ $^
	@echo -e "\e[1;36m$@ Complete\e[1;m"

Startup/startup_stm32g071xx.o: Startup/startup_stm32g071xx.s
	@arm-none-eabi-gcc $(CFLAGS) -o $@ $^
	$(OUTPUT)

%.o: %.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)


.PHONY: hex
hex: $(LINK_TARGET).elf
	@arm-none-eabi-objcopy -O binary $(LINK_TARGET).elf $(LINK_TARGET).bin
	@echo -e "\e[1;36mCreating $(LINK_TARGET).bin\e[1;m"

.PHONY: size
size: $(LINK_TARGET).elf
	@arm-none-eabi-size $(LINK_TARGET).elf \
     | xargs -I {} echo -e "\e[1;32m{}\e[1;m"

.PHONY: clean
clean:
	@rm -f $(OBJS)
	@rm -f $(LINK_TARGET).map
	@rm -f $(LINK_TARGET).elf
	@rm -f $(LINK_TARGET).bin
	@echo -e "Project Cleaned"
