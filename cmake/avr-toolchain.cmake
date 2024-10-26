# the name of the target system should be "Generic" since there is no OS
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "avr2")

# specifying C compiler is enough for the entire GNU toolchain
set(CMAKE_C_COMPILER avr-gcc)

# target toolchain prefix
set(CMAKE_FIND_ROOT_PATH ~/local/avr)

# search everything in under the target prefix
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

message("CMAKE_ASM_COMPILER=${CMAKE_ASM_COMPILER}")
message("CMAKE_C_COMPILER=${CMAKE_C_COMPILER}")
message("CMAKE_ASM_COMPILER_ID=${CMAKE_ASM_COMPILER_ID}")
message("CMAKE_C_COMPILER_ID=${CMAKE_C_COMPILER_ID}")
