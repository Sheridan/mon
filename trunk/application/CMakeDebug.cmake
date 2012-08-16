# %Id [4fd8d88:dcd59c7,05f4e55] Thu Aug 16 19:18:36 2012 +0400 Горлов Максим "Правки idter`а" %
OPTION ( BUILD_DEBUG "Build the project using debugging code" OFF )

IF( BUILD_DEBUG )
    MESSAGE ( STATUS "---> Build with debug info" )
    SET( CMAKE_BUILD_TYPE Debug )
    SET( CMAKE_VERBOSE_MAKEFILE ON )
    ADD_DEFINITIONS( -DMON_DEBUG )
ELSE( BUILD_DEBUG )
    IF(UNIX)
        ADD_DEFINITIONS( -O2 )
    ENDIF(UNIX)
ENDIF( BUILD_DEBUG )

IF(UNIX)
    ADD_DEFINITIONS( -Wall )
ENDIF(UNIX)
