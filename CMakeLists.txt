cmake_minimum_required(VERSION 3.28)
project(allocator)

set(CMAKE_C_STANDARD 99)

add_executable(
    ${PROJECT_NAME}
    main.c
    allocator/allocator.c
)

target_compile_options(
    ${PROJECT_NAME} PUBLIC
    -Werror -Wall -Wextra -fdiagnostics-color=always
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    .
)