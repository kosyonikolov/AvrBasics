cmake_minimum_required(VERSION 3.0.0)
project(AvrTest VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_options(-mmcu=atmega328p)
add_link_options(-mmcu=atmega328p)

add_executable(AvrTest src/main.cpp src/usart.cpp)
target_include_directories(AvrTest PRIVATE inc/)
target_compile_definitions(AvrTest PRIVATE -DF_CPU=16000000)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
