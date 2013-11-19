# %Id%
include(${CMAKE_INSTALL_PREFIX}/include/mon/CMakeCompiler.cmake)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

cmake_policy(POP)

include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeDebug.cmake)
set( GEN_PATH "${PROJECT_BINARY_DIR}/mon_generated_sources" )
set( SENSOR_DEFINITION "${GEN_PATH}/definition.h" )
set( SENSOR_HEADER "${GEN_PATH}/mon-sensor-${EXECUTABLE_NAME}.h" )
set( MON_LIB_DIRECTORY "${CMAKE_INSTALL_PREFIX}/lib/mon/global")
file(MAKE_DIRECTORY ${GEN_PATH})

function(add_sensor project_name executable_name sources headers include_paths)
  MESSAGE( STATUS "---------- Processing `${executable_name}` sensor ----------" )
  PROJECT(${project_name})

  file(READ ${CMAKE_INSTALL_PREFIX}/include/mon/sensor-defines.h SENSOR_HEADER_TEXT)
  string(REPLACE "%sensor_name%" ${executable_name} SENSOR_HEADER_TEXT "${SENSOR_HEADER_TEXT}" )
  file(WRITE ${SENSOR_HEADER} "${SENSOR_HEADER_TEXT}")

  add_custom_command(
    OUTPUT    ${GEN_PATH}/definition.h
    COMMAND   ${CMAKE_INSTALL_PREFIX}/bin/mon-text-to-char-array
    ARGS      ${CMAKE_SOURCE_DIR}/src/definition.txt ${SENSOR_DEFINITION} definition
    DEPENDS   ${CMAKE_SOURCE_DIR}/src/definition.txt
    COMMENT   "Convert sensor definition to C char array"
  )
  include_directories( ${CMAKE_INSTALL_PREFIX}/include/mon ${GEN_PATH} ${include_paths})
  LINK_DIRECTORIES( ${MON_LIB_DIRECTORY} )
  add_library( ${executable_name} SHARED ${sources} ${headers} ${SENSOR_DEFINITION})
  TARGET_LINK_LIBRARIES( ${executable_name} config logger sensorplugin base)
  INSTALL( TARGETS ${executable_name} LIBRARY DESTINATION lib/mon/sensors )
endfunction()
