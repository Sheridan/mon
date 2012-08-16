# %Id%
PROJECT(mon-sensor-memory)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET( EXECUTABLE_NAME memory )

include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeDebug.cmake)
include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeSensor.cmake)

MESSAGE ( STATUS "---------- Configuring mon-sensor-memory ----------" )

SET(mon-sensor-memory-sources
	src/main.cpp
)

SET(mon-sensor-memory-headers  src/main.cpp)

add_sensor(${mon-sensor-memory-sources} ${mon-sensor-memory-headers} src)
