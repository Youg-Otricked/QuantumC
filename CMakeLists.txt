cmake_minimum_required(VERSION 3.13)
project(qc LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(APPLE)
    set(CMAKE_CXX_STANDARD 20)
endif()
if(LLVM_VERSION_MAJOR LESS 21)
    message(FATAL_ERROR "LLVM 21+ required, found ${LLVM_VERSION_MAJOR}")
endif()
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFI REQUIRED IMPORTED_TARGET libffi)
option(ENABLE_LLVM "Enable LLVM-based compiler" ON)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/runtime.ll
    COMMAND clang++ -S -emit-llvm -O3 ${CMAKE_CURRENT_SOURCE_DIR}/runtime.cpp -o ${CMAKE_CURRENT_SOURCE_DIR}/runtime.ll
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/runtime.cpp
    VERBATIM
)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/runtime_embed.cpp
    COMMAND ${CMAKE_COMMAND}
        -DRUNTIME_LL=${CMAKE_CURRENT_SOURCE_DIR}/runtime.ll
        -DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/runtime_embed.cpp
        -DTEMPLATE=${CMAKE_CURRENT_SOURCE_DIR}/runtime_embed.cpp.in
        -P ${CMAKE_CURRENT_SOURCE_DIR}/embed_runtime.cmake
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/runtime.ll
    VERBATIM
)
set(SOURCES
    compiler.cpp
    compiler_run.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/runtime_embed.cpp
)
add_executable(qc ${SOURCES})

target_compile_options(qc PRIVATE
    -O0
    -g
    $<$<CXX_COMPILER_ID:GNU>:-fconstexpr-ops-limit=1000000000>
)

if(ENABLE_LLVM)
    find_package(LLVM REQUIRED CONFIG)
    separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND "${LLVM_DEFINITIONS}")
    add_definitions(${LLVM_DEFINITIONS_LIST})
    add_definitions(-D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

    target_compile_definitions(qc PRIVATE ENABLE_LLVM)
    target_include_directories(qc PRIVATE ${LLVM_INCLUDE_DIRS})
    llvm_map_components_to_libnames(llvm_libs
        Core
        Support
        IRReader
        Passes
        Analysis
        TransformUtils
        ScalarOpts
        InstCombine
        IPO
        Target
        MC
        AsmPrinter
        CodeGen
        X86CodeGen
        AllTargetsDescs
        AllTargetsAsmParsers
        AllTargetsCodeGens
    )
    target_link_libraries(qc PRIVATE ${llvm_libs} ${LLVM_SYSTEM_LIBS})
endif()

target_include_directories(qc PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FFI_INCLUDE_DIRS}
)
target_link_libraries(qc PRIVATE PkgConfig::FFI)