option(USE_CLANG "build application with clang" OFF)

if( MON_USE_CLANG )
  MESSAGE ( STATUS "---> Build with clang" )
  set( CMAKE_C_COMPILER clang)
  set( CMAKE_CXX_COMPILER clang++)
  set(MON_USE_GCC OFF)
else( MON_USE_CLANG )
  MESSAGE ( STATUS "---> Build with gcc" )
  set(CMAKE_C_COMPILER gcc)
  set(CMAKE_CXX_COMPILER g++)
endif( MON_USE_CLANG )

ADD_DEFINITIONS( -std=c++11 )