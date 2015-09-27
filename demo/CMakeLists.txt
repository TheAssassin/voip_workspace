cmake_minimum_required( VERSION 3.3 )

project( VoIP_Demos )

include_directories( ${VOIP_EXT_INC_DIR} )

add_executable( hello_rtaudio hello_rtaudio.cpp )
target_link_libraries( hello_rtaudio ${VOIP_EXT_LIBS} )

add_executable( tonegen tonegen.cpp )
target_link_libraries( tonegen ${VOIP_EXT_LIBS} )
