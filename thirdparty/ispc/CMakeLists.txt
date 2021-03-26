
MESSAGE( STATUS "USE_ISPC: " ${USE_ISPC})

IF(USE_ISPC)
    IF(${WIN32})
        EXECUTE_PROCESS(
            COMMAND ispc.exe --version 
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/windows/)
    ELSE()
        EXECUTE_PROCESS(
            COMMAND ispc --version 
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/linux/)
    ENDIF(${WIN32})
ENDIF(USE_ISPC)