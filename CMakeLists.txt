cmake_minimum_required( VERSION 3.0 )

project( VoIP )

set( BUILD_TESTING OFF CACHE BOOL "Build tests (includes tests in all subprojects)." )
set( VOIP_BUILD_DEMOS ON CACHE BOOL "Build demo applications." )
set( VOIP_BUILD_ASSIGNMENTS OFF CACHE BOOL "Build assignments.")

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_subdirectory( ext/rtaudio )
add_subdirectory( toolbox )

set( VOIP_EXT_LIBS    rtaudio voip_toolbox)
set( VOIP_EXT_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/rtaudio
                      ${CMAKE_CURRENT_SOURCE_DIR}/ext/tclap/include
											${CMAKE_CURRENT_SOURCE_DIR}/toolbox/include )

if( ${VOIP_BUILD_DEMOS} )
  add_subdirectory( demo )
endif()

if( ${VOIP_BUILD_ASSIGNMENTS} )
  add_subdirectory( assignments )
endif()
