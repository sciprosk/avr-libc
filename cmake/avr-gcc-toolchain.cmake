# the name of the target system should be "Generic" since there is no OS
set(CMAKE_SYSTEM_NAME "Linux") # changing this to Generic shanges file extensions to "*.obj"
set(CMAKE_SYSTEM_PROCESSOR "avr2")

# specifying C compiler is enough for the entire GNU toolchain
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)
set(CMAKE_C_FLAGS_INIT "-mmcu=atmega328p")
#set(CMAKE_ASM_FLAGS_INIT "-mmcu=atmega328p")

set(CMAKE_EXE_LINKER_FLAGS_INIT "-mmcu=atmega328p")

# target toolchain prefix
set(CMAKE_FIND_ROOT_PATH ~/local/avr)

# search everything in under the target prefix
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
