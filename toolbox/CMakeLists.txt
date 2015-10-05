cmake_minimum_required( VERSION 3.0 )

project( VoIP_Toolbox )

include_directories( include )

set( SRC  src/audiobuffer.cpp
          src/posix/socket_posix.cpp )

set( HDR  include/audiobuffer.h
          include/socket.h )

add_library( voip_toolbox ${SRC} )
