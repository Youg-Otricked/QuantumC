cmake_minimum_required(VERSION 3.13)
project(qc LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(APPLE OR EMSCRIPTEN)
    set(CMAKE_CXX_STANDARD 20)
endif()
find_package(LLVM REQUIRED CONFIG)
if(LLVM_VERSION_MAJOR LESS 21)
    message(FATAL_ERROR "LLVM 21+ required, found ${LLVM_VERSION_MAJOR}")
endif()
option(ENABLE_LLVM "Enable LLVM-based compiler" ON)
option(CXX_RUNTIME "Build runtime.ll from runtime.cpp instead of runtime.qc" OFF)
if(CXX_RUNTIME)
set(COMPILER_FOR_RUNTIME "clang++")
if(EMSCRIPTEN)
    set(COMPILER_FOR_RUNTIME "em++")
endif()
else()
    if(NOT QC_EXECUTABLE)
        find_program(QC_EXECUTABLE NAMES qc REQUIRED)
    endif()
    if(NOT QC_EXECUTABLE)
        message(FATAL_ERROR "QC_EXECUTABLE was not provided and qc was not found in PATH")
    endif()
    message(STATUS "Using QC runtime compiler: ${QC_EXECUTABLE}")
endif()
if(CXX_RUNTIME)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/runtime.ll
    COMMAND ${COMPILER_FOR_RUNTIME} ${RUNTIME_TARGET_FLAGS} -S -emit-llvm -O3 ${CMAKE_CURRENT_SOURCE_DIR}/runtime.cpp -o ${CMAKE_CURRENT_SOURCE_DIR}/runtime.ll
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/runtime.cpp
    VERBATIM
)
else()
add_custom_command(
    OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/runtime.ll"
    COMMAND "${QC_EXECUTABLE}" -co -nrt -O3
            "${CMAKE_CURRENT_SOURCE_DIR}/runtime.qc"
            -o "${CMAKE_CURRENT_SOURCE_DIR}/runtime.ll"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/runtime.qc"
    VERBATIM
)
endif()
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
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:RelWithDebInfo>:-O2>

    $<$<CXX_COMPILER_ID:GNU>:-fconstexpr-ops-limit=1000000000>
)
if(ENABLE_LLVM)
    separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND "${LLVM_DEFINITIONS}")
    add_definitions(${LLVM_DEFINITIONS_LIST})
    add_definitions(-D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
    target_compile_definitions(qc PRIVATE ENABLE_LLVM)
    target_include_directories(qc PRIVATE ${LLVM_INCLUDE_DIRS})
    set(LLVM_COMPONENTS
        Core Support IRReader Passes Analysis TransformUtils 
        ScalarOpts InstCombine IPO Target MC AsmPrinter CodeGen
    )
    if(EMSCRIPTEN)
        list(APPEND LLVM_COMPONENTS
            WebAssemblyCodeGen WebAssemblyAsmParser WebAssemblyDesc
        )
    else()
        list(APPEND LLVM_COMPONENTS
            X86CodeGen AllTargetsDescs AllTargetsAsmParsers AllTargetsCodeGens
            WebAssemblyCodeGen WebAssemblyAsmParser WebAssemblyDesc
        )
    endif()
    llvm_map_components_to_libnames(llvm_libs ${LLVM_COMPONENTS})
    target_link_libraries(qc PRIVATE ${llvm_libs} ${LLVM_SYSTEM_LIBS})
endif()
target_include_directories(qc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
if(EMSCRIPTEN)
    message(STATUS "Detected Emscripten environment - Applying WASM configuration")
    add_definitions(-D__EMSCRIPTEN__)
    add_definitions(-D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
    if(NOT LLVM_WASM_PATH)
        set(LLVM_WASM_PATH "/usr/lib/llvm-21")
    endif()
    include_directories("${LLVM_WASM_PATH}/include")
    set_target_properties(qc PROPERTIES 
        OUTPUT_NAME "qc"
        SUFFIX ".js"
        LINK_FLAGS "\
            -s WASM=1 \
            -s FORCE_FILESYSTEM=1 \
            -s EXPORTED_FUNCTIONS='[\"_run_quantumc_code\"]' \
            -s EXPORTED_RUNTIME_METHODS='[\"ccall\",\"cwrap\",\"FS\"]' \
            -s ALLOW_MEMORY_GROWTH=1 \
            --preload-file ${CMAKE_SOURCE_DIR}/stdlib.qc@/stdlib.qc \
            -s STACK_SIZE=134217728 \
            -s MODULARIZE=1 \
            -s EXPORT_NAME=\"QuantumC\" \
            -s TOTAL_MEMORY=805306368 \
            -s ASSERTIONS=1 \
            -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE='[\"$stackSave\",\"$stackRestore\",\"$stackAlloc\"]'\
            -Oz \
            -s NO_DISABLE_EXCEPTION_CATCHING"
    )
endif()
