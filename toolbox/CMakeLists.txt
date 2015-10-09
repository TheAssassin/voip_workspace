cmake_minimum_required( VERSION 3.0 )

project( VoIP_Toolbox )

include_directories( include )

set( SRC  src/audiobuffer.cpp )

set( POSIX_SRC src/posix/socket_posix.cpp )

set( WIN_SRC src/win/socket_win.cpp )

if( ${CMAKE_SYSTEM_NAME} STREQUAL Windows )
  list( APPEND SRC ${WIN_SRC} )
else()
  list( APPEND SRC ${POSIX_SRC} )
endif()

set( HDR  include/audiobuffer.h
          include/socket.h )

add_library( voip_toolbox ${SRC} )
