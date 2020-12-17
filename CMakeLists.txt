cmake_minimum_required(VERSION 3.16)
project(ElectronicLoad)

enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(EXECUTABLE ${PROJECT_NAME}.elf)

set(SRC_FILES
    Startup/startup_stm32g071xx.s
    Src/main.c
    Src/system_init.c
    Src/system_stm32f0xx.c
    Src/adc.c
    Src/gpio.c
    Src/tim.c
    Src/uart.c)

add_executable(${EXECUTABLE} ${SRC_FILES})

target_include_directories(${EXECUTABLE} PRIVATE
    Inc
    Drivers/CMSIS/Include
    Drivers/CMSIS/Device/ST/STM32G0xx/Include)

target_compile_definitions(${EXECUTABLE} PRIVATE
    -DSTM32G071xB
    )

target_compile_options(${EXECUTABLE} PRIVATE
    -mcpu=cortex-m0+
    -g3
    -O0
    -ffunction-sections
    -fdata-sections
    -Wall
    -fstack-usage
    --specs=nano.specs
    -mfloat-abi=soft
    -mthumb
    )

target_link_options(${EXECUTABLE} PRIVATE
    -T/home/gareth/Documents/Electronics/Projects/XenonPansy/STM32/STM32G071RBTX_FLASH.ld
    -mcpu=cortex-m0+
    -mthumb
    -mfloat-abi=soft
    --specs=nosys.specs
    --specs=nano.specs
    -Wl,-Map=ElectronicLoad.map
    -Wl,--gc-sections
    -static
    )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size ${EXECUTABLE}
    )


# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
    )
