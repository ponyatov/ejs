# host compiler
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_BUILD_TYPE  Debug)
set(TOOLCHAIN_PREFIX  ${ARCH}-${OS}-gnu)

# cross compilers to use for C and C++
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

add_definitions(
    "LINUX", "X86_64", OS=${OS}, HW=${HW}
)
