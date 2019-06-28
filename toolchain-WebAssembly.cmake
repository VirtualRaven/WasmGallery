set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_NAME "Generic")

set(TARGET wasm32 )

# specify the cross compiler
SET(CMAKE_C_COMPILER_TARGET ${TARGET})
SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER_TARGET ${TARGET})
SET(CMAKE_CXX_COMPILER clang++)
SET(CMAKE_ASM_COMPILER_TARGET ${TARGET})
SET(CMAKE_ASM_COMPILER clang)
SET(CMAKE_CXX_FLAGS "-nostdlib "  )
set(CMAKE_EXE_LINKER_FLAGS " -Wl,--no-entry -Wl,--export-all -Wl,--demangle -flto -Oz -Wl-lto-Oz -Wl,--no-gc-sections "  )