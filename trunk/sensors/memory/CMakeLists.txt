# %Id%
include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeSensor.cmake)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(mon-sensor-memory-sources
    src/main.cpp)
SET(mon-sensor-memory-headers
    src/main.cpp)
SET(include_dirs
    src)

add_sensor(mon-sensor-memory memory ${mon-sensor-memory-sources} ${mon-sensor-memory-headers} ${include_dirs})
