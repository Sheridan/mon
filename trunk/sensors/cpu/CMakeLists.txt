PROJECT(mon-sensor-cpu)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET( EXECUTABLE_NAME cpu )

include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeDebug.txt)

MESSAGE ( STATUS "---------- Configuring mon-sensor-cpu ----------" )

SET(mon-sensor-cpu-sources
	src/main.cpp
)

SET(mon-sensor-cpu-headers
)

add_library( ${EXECUTABLE_NAME} SHARED
	     ${mon-sensor-cpu-sources}
	     ${mon-sensor-cpu-headers} )

target_link_libraries( ${EXECUTABLE_NAME} )

INSTALL(TARGETS ${EXECUTABLE_NAME}
        LIBRARY DESTINATION lib/mon/sensors
)
