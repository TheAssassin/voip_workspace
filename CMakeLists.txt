cmake_minimum_required( VERSION 3.0 )

project( VoIP )

set( BUILD_TESTING OFF CACHE BOOL "Build tests (includes tests in all subprojects)." )
set( VOIP_BUILD_OPUS OFF CACHE BOOL "Build opus audio coding library." )
set( VOIP_BUILD_DEMOS ON CACHE BOOL "Build demo applications." )
set( VOIP_BUILD_ASSIGNMENTS OFF CACHE BOOL "Build assignments.")
set( VOIP_BUILD_SOLUTIONS OFF CACHE BOOL "Build solutions (check only, if you have them ;).")

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(${COMPILER_SUPPORTS_CXX11})
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	endif()
endif()

set( VOIP_EXT_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/rtaudio
                      ${CMAKE_CURRENT_SOURCE_DIR}/ext/tclap/include
											${CMAKE_CURRENT_SOURCE_DIR}/toolbox/include )

if( ${VOIP_BUILD_OPUS} )
	add_subdirectory( ext/opus )
	list( APPEND VOIP_EXT_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/opus/include )
endif()

add_subdirectory( ext/rtaudio )
add_subdirectory( toolbox )

if( ${CMAKE_SYSTEM_NAME} STREQUAL Windows)
	set( VOIP_EXT_LIBS    rtaudio_static voip_toolbox ws2_32)
else()
	set( VOIP_EXT_LIBS    rtaudio voip_toolbox)
endif()

if( ${VOIP_BUILD_DEMOS} )
  add_subdirectory( demo )
endif()

if( ${VOIP_BUILD_ASSIGNMENTS} )
  add_subdirectory( assignments )
endif()
