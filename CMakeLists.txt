cmake_minimum_required(VERSION 3.13)
project(qc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFI REQUIRED libffi)

option(ENABLE_LLVM "Enable LLVM-based compiler" ON)

set(SOURCES
    compiler.cpp
    compiler_run.cpp
)

add_executable(qc ${SOURCES})

target_compile_options(qc PRIVATE
    -O0
    -fconstexpr-ops-limit=1000000000
    -g
)

target_include_directories(qc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FFI_INCLUDE_DIRS}
)

if(ENABLE_LLVM)
    target_compile_definitions(qc PRIVATE ENABLE_LLVM)

    target_include_directories(qc PRIVATE
        /usr/lib/llvm-18/include
    )

    target_link_directories(qc PRIVATE
        /usr/lib/llvm-18/lib
    )

    target_link_libraries(qc PRIVATE
        LLVM-18
    )
endif()
target_link_libraries(qc PRIVATE ${FFI_LIBRARIES})