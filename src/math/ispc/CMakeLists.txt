set(FUNCTIONS op_common op_matrix op_vector)

foreach(FUNC IN LISTS FUNCTIONS)
    IF(APPLE)
        add_custom_command(OUTPUT ${FUNC}.o
            COMMAND ${CMAKE_COMMAND} -E env "PATH=${ISPC_COMPILER_PATH}" ${ISPC_COMPILER} ${ISPC_OPTIONS} -o ${FUNC}.o ${CMAKE_CURRENT_SOURCE_DIR}/${FUNC}.ispc
            MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${FUNC}.ispc
            COMMENT "Building ${FUNC}"
            )
    ELSEIF(${CMAKE_HOST_SYSTEM_NAME} MATCHES Windows)
        add_custom_command(OUTPUT ${FUNC}.o
            COMMAND ${CMAKE_COMMAND} -E env "PATH=${ISPC_COMPILER_PATH}" ${ISPC_COMPILER} ${ISPC_OPTIONS} -o ${FUNC}.o ${CMAKE_CURRENT_SOURCE_DIR}/${FUNC}.ispc
            MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${FUNC}.ispc
            COMMENT "Building ${FUNC}"
            )
    ELSE()
        add_custom_command(OUTPUT ${FUNC}.o
            COMMAND ${CMAKE_COMMAND} -E env "PATH=${ISPC_COMPILER_PATH}" ${ISPC_COMPILER} ${ISPC_OPTIONS} -o ${FUNC}.o ${CMAKE_CURRENT_SOURCE_DIR}/${FUNC}.ispc
            MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${FUNC}.ispc
            COMMENT "Building ${FUNC}"
            )
    ENDIF()

    list(APPEND OBJECTS ${FUNC}.o)

endforeach(FUNC)

IF(${WIN32})
add_custom_command(OUTPUT ${LINEAR_ALGEBRA_LIB_FILE}
        COMMAND ${CMAKE_AR} ${ISPC_LIBRARIAN_OPTIONS} ${OBJECTS}
        DEPENDS ${OBJECTS}
        )
ELSE(${WIN32})
add_custom_command(OUTPUT ${LINEAR_ALGEBRA_LIB_FILE}
        COMMAND ${CMAKE_AR} ${ISPC_LIBRARIAN_OPTIONS} ${OBJECTS}
        COMMAND ${CMAKE_RANLIB} ${LINEAR_ALGEBRA_LIB_FILE}
        DEPENDS ${OBJECTS}
        )
ENDIF(${WIN32})

add_custom_target(IspcMathLib DEPENDS ${LINEAR_ALGEBRA_LIB_FILE})