cmake_minimum_required(VERSION 3.21)

project(
  kilo_editor
  VERSION 0.1.0
  DESCRIPTION "A terminal text editor written in C"
  LANGUAGES C
)

add_executable(kilo src/kilo.c)

set_target_properties(
  kilo
  PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(
    kilo
    PRIVATE
      -Wall
      -Wextra
      -Wpedantic
  )
endif()
