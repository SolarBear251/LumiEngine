# Math lib filename
SET(LUMI_MATH_LIB_FILE ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}LumiMath${CMAKE_STATIC_LIBRARY_SUFFIX})

########### ispc ############
IF(USE_ISPC)
    add_definitions(-DUSE_ISPC)
    # Platforms
    IF(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
        SET(ISPC_COMPILER_PATH ${PROJECT_SOURCE_DIR}/thirdparty/ispc/windows/)
        SET(ISPC_COMPILER ispc.exe)
        IF(NOT ${CMAKE_CROSSCOMPILING})
            if(${MSVC})
                SET(CMAKE_AR lib)
                if(${ARCH_BIT} MATCHES 64)
                    SET(ISPC_OPTIONS --arch=x86-64 --target=host)
                    SET(ISPC_LIBRARIAN_OPTIONS /MACHINE:X64 /OUT:${LUMI_MATH_LIB_FILE})
                else()
                    SET(ISPC_OPTIONS --arch=x86 --target=host)
                    SET(ISPC_LIBRARIAN_OPTIONS /MACHINE:X86 /OUT:${LUMI_MATH_LIB_FILE})
                endif()
            else()
                if(${ARCH_BIT} MATCHES 64)
                    SET(ISPC_OPTIONS --arch=x86-64 --target=host)
                else()
                    SET(ISPC_OPTIONS --arch=x86 --target=host)
                endif()
                SET(ISPC_LIBRARIAN_OPTIONS -rcv ${LUMI_MATH_LIB_FILE})
            endif(${MSVC})
        ELSE()
            if(PSP2)
                SET(ISPC_OPTIONS --arch=arm --cpu=cortex-a9 --target=neon-i32x4)
                SET(CMAKE_AR ${SNC_TOOLCHAIN_DIR}psp2snarl -rcv ${LUMI_MATH_LIB_FILE})
            endif()
        ENDIF()
    ELSE()
        SET(ISPC_COMPILER_PATH ${PROJECT_SOURCE_DIR}/thirdparty/ispc/linux/)
        SET(ISPC_COMPILER ispc)
        SET(ISPC_OPTIONS --arch=x86-64 --target=host --pic)
        SET(ISPC_LIBRARIAN_OPTIONS -rcv -o ${LUMI_MATH_LIB_FILE})
    ENDIF(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")

    # common options for ispc
    SET(ISPC_OPTIONS ${ISPC_OPTIONS} -O2)
    add_subdirectory(ispc)
ENDIF(USE_ISPC)


add_library(LumiMath
    op_common.cpp
    op_vector.cpp
    op_matrix.cpp
)
target_include_directories(LumiMath INTERFACE ${PROJECT_SOURCE_DIR}/include/math)
IF(USE_ISPC)
    add_dependencies(LumiMath LumiIspc)
ENDIF(USE_ISPC)

set_target_properties(LumiMath
    PROPERTIES
    IMPORTED_LOCATION ${LUMI_MATH_LIB_FILE}
)