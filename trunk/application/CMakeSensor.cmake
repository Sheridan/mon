# %Id%
include (${CMAKE_INSTALL_PREFIX}/include/mon/CMakeDebug.cmake)
set( GEN_PATH "${PROJECT_BINARY_DIR}/mon_generated_sources" )
set( SENSOR_DEFINITION "${GEN_PATH}/definition.h" )
set( SENSOR_HEADER "${GEN_PATH}/${EXECUTABLE_NAME}.h" )
set( MON_LIB_DIRECTORY "${CMAKE_INSTALL_PREFIX}/lib/mon/global")
file(MAKE_DIRECTORY ${GEN_PATH})

file(READ ${CMAKE_INSTALL_PREFIX}/include/mon/sensor-defines.h SENSOR_HEADER_TEXT)

string(REPLACE "%sensor_name%" ${EXECUTABLE_NAME} SENSOR_HEADER_TEXT "${SENSOR_HEADER_TEXT}" )

file(WRITE ${SENSOR_HEADER} "${SENSOR_HEADER_TEXT}")

function(add_sensor sources headers include_paths)
  MESSAGE( STATUS "---------- Processing `${EXECUTABLE_NAME}` sensor ----------" )
  add_custom_command(
    OUTPUT    ${GEN_PATH}/definition.h
    COMMAND   ${CMAKE_INSTALL_PREFIX}/bin/mon-text-to-char-array
    ARGS      ${CMAKE_SOURCE_DIR}/src/definition.txt ${SENSOR_DEFINITION} definition
    DEPENDS   ${CMAKE_SOURCE_DIR}/src/definition.txt
    COMMENT   "Convert sensor definition to C char array"
  )
  include_directories( ${CMAKE_INSTALL_PREFIX}/include/mon ${GEN_PATH} ${include_paths})
  LINK_DIRECTORIES( ${MON_LIB_DIRECTORY} )
  add_library( ${EXECUTABLE_NAME} SHARED ${sources} ${headers} ${SENSOR_DEFINITION})
  TARGET_LINK_LIBRARIES( ${EXECUTABLE_NAME} config logger base )
  INSTALL( TARGETS ${EXECUTABLE_NAME} LIBRARY DESTINATION lib/mon/sensors )
endfunction()
