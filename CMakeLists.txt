cmake_minimum_required(VERSION 3.19)

project(avr-libc
    VERSION 2.3.0
    DESCRIPTION "C standard library for AVR devices"
    HOMEPAGE_URL "https://github.com/sciprosk/avr-libc"
    LANGUAGES C ASM
)

set(ASM_OPTIONS "-x assembler-with-cpp")
set(CMAKE_ASM_FLAGS "${CFLAGS} ${ASM_OPTIONS} ")

add_subdirectory(libc)
add_subdirectory(libm)

