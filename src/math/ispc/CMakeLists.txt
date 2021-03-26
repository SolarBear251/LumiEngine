set(FUNCTIONS op_common op_matrix op_vector)

foreach(FUNC IN LISTS FUNCTIONS)
    add_custom_command(OUTPUT ${FUNC}.o
        COMMAND ${CMAKE_COMMAND} -E env "PATH=${ISPC_COMPILER_PATH}" ${ISPC_COMPILER} ${ISPC_OPTIONS} -o ${FUNC}.o ${CMAKE_CURRENT_SOURCE_DIR}/${FUNC}.ispc
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${FUNC}.ispc
        COMMENT "Building ${FUNC}"
        )
    list(APPEND OBJECTS ${FUNC}.o)

endforeach(FUNC)

IF(${WIN32})
add_custom_command(OUTPUT ${LUMI_MATH_LIB_FILE}
        COMMAND ${CMAKE_AR} ${ISPC_LIBRARIAN_OPTIONS} ${OBJECTS}
        DEPENDS ${OBJECTS}
        )
ELSE()
add_custom_command(OUTPUT ${LUMI_MATH_LIB_FILE}
        COMMAND ${CMAKE_AR} ${ISPC_LIBRARIAN_OPTIONS} ${OBJECTS}
        COMMAND ${CMAKE_RANLIB} ${LUMI_MATH_LIB_FILE}
        DEPENDS ${OBJECTS}
        )
ENDIF(${WIN32})

add_custom_target(LumiIspc DEPENDS ${LUMI_MATH_LIB_FILE})