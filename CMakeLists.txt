cmake_minimum_required(VERSION 3.2)
project("ImgLayout" CXX)

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/layout.cpp")
if(NOT CMAKE_CROSSCOMPILING)
    set(SRC "${SRC}"
            "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    )
else()
    set(CMAKE_EXECUTABLE_SUFFIX ".wasm")
    add_definitions(-DTARGET_WASM)
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -fno-exceptions")
SET(EXE_NAME ${CMAKE_PROJECT_NAME} )
add_executable(${EXE_NAME} "${SRC}")
if( CMAKE_CROSSCOMPILING)
    set(MIN_WASM "${EXE_NAME}-min.wasm")
    set(MIN_WAT  "${EXE_NAME}-min.wat")
    add_custom_command(OUTPUT "${MIN_WASM}" 
                       COMMAND wasm-opt -Oz  $<TARGET_FILE:${EXE_NAME}> -o "${MIN_WASM}" 
                       DEPENDS ${EXE_NAME} )

    add_custom_command(OUTPUT ${MIN_WAT}
                       COMMAND wasm2wat -f ${MIN_WASM} -o ${MIN_WAT} 
                       DEPENDS ${MIN_WASM})
    add_custom_target(minASM ALL DEPENDS ${MIN_WAT} )
endif()