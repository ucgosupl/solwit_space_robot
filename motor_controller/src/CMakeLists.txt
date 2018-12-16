cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE Toolchain-arm-gcc.cmake)

# Allow assembler
enable_language(ASM)

project(solwit_space_robot)

#todo: compile rosserial_client in separate cmake to static library
set(INCLUDE_DIRS
	.
    utils
    external/stm32
    external/cmsis
	external/ros_lib
)

set(CPP_SRCS
	hw/dma/Dma.cpp
	hw/gpio/Gpio.cpp
	hw/tb6612/Motor.cpp
	hw/tb6612/Motor_driver.cpp
	hw/time/Time.cpp
	hw/uart/Uart.cpp
	hw/uart/Utility.cpp
	hw/uart/Serial.cpp
	code/App/App.cpp
	code/Rosserial/Stm32_client.cpp
	external/ros_lib/duration.cpp
	external/ros_lib/time.cpp
)

set(C_SRCS
    hw/core_init/core_init.c
	hw/gpio/gpio_f4.c
	hw/startup/hardfault.c
    hw/startup/vectors.c
    utils/syscalls.c
	main.c
)

set(ASM_SRCS
    hw/startup/startup.S
)

set(GLOBAL_DEFINES
    -DSTM32F40_41xxx
)

set(LINKED_LIBS

)

link_directories(

)

include_directories(${INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

include(compiler_flags.cmake)
include(cppcheck.cmake)

# generate elf file
add_arm_executable(${CMAKE_PROJECT_NAME} ${CPP_SRCS} ${C_SRCS} ${ASM_SRCS})

arm_link_libraries(${CMAKE_PROJECT_NAME} ${LINKED_LIBS})
