# %Id%
PROJECT(mon-sensor-memory)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET( EXECUTABLE_NAME memory )

include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeDebug.txt)

MESSAGE ( STATUS "---------- Configuring mon-sensor-memory ----------" )

SET(mon-sensor-memory-sources
	src/main.cpp
)

SET(mon-sensor-memory-headers
)

add_library( ${EXECUTABLE_NAME} SHARED
	     ${mon-sensor-memory-sources}
	     ${mon-sensor-memory-headers} )

target_link_libraries( ${EXECUTABLE_NAME} )

INSTALL(TARGETS ${EXECUTABLE_NAME}
        LIBRARY DESTINATION lib/mon/sensors
)
