###############################################
# CMake script to build Electronic Load Project
# Written by Gareth Waymark UP762102
###############################################

cmake_minimum_required(VERSION 3.16)
project(ElectronicLoad)

enable_language(C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

set(EXECUTABLE ${PROJECT_NAME}.elf)

set(SRC_FILES
        Startup/startup_stm32g071xx.s
        Src/main.c
        Src/init.c
        Src/system_stm32g0xx.c
        Src/clock_tree.c
        Src/gpio.c
        Src/interrupts.c
        Src/dac.c
        Src/display.c
        Src/st7066u_lcd.c
        Src/syscalls.c
        Src/proj_tasks.c
        #FreeRTOS/Source/tasks.c
        #FreeRTOS/Source/list.c
        #FreeRTOS/Source/queue.c
        #FreeRTOS/Source/timers.c
        #FreeRTOS/Source/portable/MemMang/heap_3.c
        #FreeRTOS/Source/portable/GCC/ARM_CM0/port.c
        #~/Documents/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.c
        #~/Documents/SEGGER/SEGGER_SYSVIEW_FreeRTOS.c
        #~/Documents/SEGGER/SEGGER_SYSVIEW_Config_FreeRTOS.c
        #~/Documents/SEGGER/SEGGER_SYSVIEW.c
        #~/Documents/SEGGER/SEGGER_RTT.c
        #~/Documents/SEGGER/SEGGER_RTT_printf.c
        #~/Documents/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.c
        
        
)

add_executable(${EXECUTABLE} ${SRC_FILES})

target_include_directories(${EXECUTABLE} PRIVATE
    Inc
    Drivers/CMSIS/Include
    Drivers/CMSIS/Device/ST/STM32G0xx/Include
    #FreeRTOS/Source/include
    #FreeRTOS/Source/portable/GCC/ARM_CM0
    #~/Documents/SEGGER
)

target_compile_definitions(${EXECUTABLE} PRIVATE
    -DSTM32G071xx
    )

target_compile_options(${EXECUTABLE} PRIVATE
    -mcpu=cortex-m0plus
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
    -T/home/gareth/Dropbox/Uni/L6/Individual_Project/STM32/STM32G071CBTx_FLASH.ld
    -mcpu=cortex-m0plus
    -mthumb
    -mfloat-abi=soft
    --specs=nosys.specs
    --specs=nano.specs
    -Wl,-Map=build/ElectronicLoad.map
    -Wl,--gc-sections
    -static
    )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-size build/${EXECUTABLE}
    )


# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary build/${EXECUTABLE} build/${PROJECT_NAME}.bin
    )
