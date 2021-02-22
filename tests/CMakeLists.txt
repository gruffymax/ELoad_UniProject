cmake_minimum_required(VERSION 3.16)
project(tests)

enable_language(C ASM)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE ${PROJECT_NAME})

set(SRC_FILES
        ~/Unity/src/unity.c
        test_task_ui.c
        ../Src/task_ui.c
)

add_executable(${EXECUTABLE} ${SRC_FILES})

target_include_directories(${EXECUTABLE} PRIVATE
    .
    ../Inc
    ~/Unity/src
)
