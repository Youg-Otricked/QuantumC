if(RUNTIMENEEDS_LL)
    find_program(LLVM_LINK llvm-link REQUIRED)
    set(MERGED_LL "${CMAKE_CURRENT_BINARY_DIR}/merged_runtime.ll")
    execute_process(
        COMMAND ${LLVM_LINK}
            "${RUNTIME_LL}"
            "${RUNTIMENEEDS_LL}"
            -S
            -o "${MERGED_LL}"
        RESULT_VARIABLE LINK_RESULT
    )
    if(NOT LINK_RESULT EQUAL 0)
        message(FATAL_ERROR "llvm-link failed")
    endif()
    set(EMBED_LL "${MERGED_LL}")
else()
    set(EMBED_LL "${RUNTIME_LL}")
endif()
file(READ "${EMBED_LL}" RUNTIME_LL_CONTENT HEX)
string(REGEX REPLACE
    "([0-9a-f][0-9a-f])"
    "0x\\1,"
    RUNTIME_LL_HEX
    "${RUNTIME_LL_CONTENT}"
)
configure_file(
    "${TEMPLATE}"
    "${OUTPUT}"
    @ONLY
)
