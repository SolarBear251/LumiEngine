# Math lib filename
SET(LUMI_MATH_LIB_FILE ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}lumi_math${CMAKE_STATIC_LIBRARY_SUFFIX})

########### ispc ############
IF(USE_ISPC)
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

    add_library(lumi_math STATIC IMPORTED GLOBAL)
    add_dependencies(lumi_math lumi_ispc)

    set_target_properties(lumi_math
        PROPERTIES
        IMPORTED_LOCATION ${LUMI_MATH_LIB_FILE}
    )
ELSE()
    add_library(lumi_math INTERFACE ${LUMI_MATH_HEADERS})
    target_include_directories(lumi_math INTERFACE ${PROJECT_SOURCE_DIR}/include/lumi/math)
ENDIF(USE_ISPC)
