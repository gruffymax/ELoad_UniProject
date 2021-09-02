# Makefile for Electronic Load Project
# Written by Gareth Waymark
# @ stops the command echo

LINK_TARGET=ElectronicLoad

INCS=-IInc \
     -IInc/Hardware \
     -IInc/Tasks \
     -IDrivers/CMSIS/Include \
     -IDrivers/CMSIS/Device/ST/STM32G0xx/Include \
     -IFreeRTOS/Source/include \
     -IFreeRTOS/Source/portable/GCC/ARM_CM0

CFLAGS=\
     -DSTM32G071xx \
     -mcpu=cortex-m0plus \
     -g3 \
     -O0 \
     -ffunction-sections \
     -fdata-sections \
     -Wall \
     -fstack-usage \
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
     -Wl,-Map=build/ElectronicLoad.map \
     -Wl,--gc-sections \
     -static

DEFS=\
     -DSTM32G071xx

SRC=Src
OUTPUT=@echo -e "\e[1;36m$@\e[1;m"

BUILD_DIR=build/

OBJS=\
     $(BUILD_DIR)startup_stm32g071xx.o \
     $(BUILD_DIR)main.o \
     $(BUILD_DIR)init.o \
     $(BUILD_DIR)system_stm32g0xx.o \
     $(BUILD_DIR)clock_tree.o \
     $(BUILD_DIR)gpio.o \
     $(BUILD_DIR)interrupts.o \
     $(BUILD_DIR)dac.o \
     $(BUILD_DIR)display.o \
     $(BUILD_DIR)st7066u_lcd.o \
     $(BUILD_DIR)syscalls.o \
     $(BUILD_DIR)task_ui.o \
     $(BUILD_DIR)task_control.o \
     $(BUILD_DIR)task_lcd.o \
     $(BUILD_DIR)pi.o \
     $(BUILD_DIR)adc.o \
     $(BUILD_DIR)tasks.o \
     $(BUILD_DIR)list.o \
     $(BUILD_DIR)queue.o \
     $(BUILD_DIR)timers.o \
     $(BUILD_DIR)heap_4.o \
     $(BUILD_DIR)port.o

all: $(LINK_TARGET).elf size hex

$(LINK_TARGET).elf: $(OBJS)
	@arm-none-eabi-gcc $(LFLAGS) $(INCS) -o $@ $^
	@echo -e "\e[1;36m$@ Complete\e[1;m"

$(BUILD_DIR)startup_stm32g071xx.o: Startup/startup_stm32g071xx.s
	@arm-none-eabi-gcc $(CFLAGS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)main.o: $(SRC)/main.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)init.o: $(SRC)/Hardware/init.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)system_stm32g0xx.o: $(SRC)/system_stm32g0xx.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)clock_tree.o: $(SRC)/Hardware/clock_tree.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)gpio.o: $(SRC)/Hardware/gpio.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)interrupts.o: $(SRC)/Hardware/interrupts.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)dac.o: $(SRC)/Hardware/dac.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)display.o: $(SRC)/Hardware/display.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)st7066u_lcd.o: $(SRC)/Hardware/st7066u_lcd.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)syscalls.o: $(SRC)/syscalls.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)task_ui.o: $(SRC)/Tasks/task_ui.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)task_control.o: $(SRC)/Tasks/task_control.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)task_lcd.o: $(SRC)/Tasks/task_lcd.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)pi.o: $(SRC)/Tasks/pi.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)adc.o: $(SRC)/Hardware/adc.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)tasks.o: FreeRTOS/Source/tasks.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)list.o:  FreeRTOS/Source/list.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)queue.o: FreeRTOS/Source/queue.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)timers.o: FreeRTOS/Source/timers.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)heap_4.o: FreeRTOS/Source/portable/MemMang/heap_4.c
	@arm-none-eabi-gcc $(CFLAGS) $(INCS) -o $@ $^
	$(OUTPUT)

$(BUILD_DIR)port.o: FreeRTOS/Source/portable/GCC/ARM_CM0/port.c
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
	@rm -f build/*.o
	@rm -f build/*.su
	@rm -f $(LINK_TARGET).elf
	@rm -f $(LINK_TARGET).bin
	@echo -e "Project Cleaned"
