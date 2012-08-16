# %Id%
PROJECT(mon-sensor-cpu)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET( EXECUTABLE_NAME cpu )

include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeDebug.cmake)
include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeSensor.cmake)

MESSAGE ( STATUS "---------- Configuring mon-sensor-cpu ----------" )

SET(mon-sensor-cpu-sources
	src/main.cpp
)

SET(mon-sensor-cpu-headers src/main.cpp)

add_sensor(${mon-sensor-cpu-sources} ${mon-sensor-cpu-headers} src)
