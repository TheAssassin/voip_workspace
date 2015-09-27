cmake_minimum_required( VERSION 3.3 )

project( VoIP )

set( BUILD_TESTING OFF CACHE BOOL "Build tests (includes tests in all subprojects)." )
set( VOIP_BUILD_DEMOS ON CACHE BOOL "Build demo applications." )
set( VOIP_BUILD_ASSIGNMENTS OFF CACHE BOOL "Build assignments.")

add_subdirectory( ext/rtaudio )

set( VOIP_EXT_LIBS    rtaudio )
set( VOIP_EXT_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/rtaudio
                      ${CMAKE_CURRENT_SOURCE_DIR}/ext/tclap/include )

if( ${VOIP_BUILD_DEMOS} )
  add_subdirectory( demo )
endif()

if( ${VOIP_BUILD_ASSIGNMENTS} )
  add_subdirectory( assignments )
endif()
