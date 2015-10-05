cmake_minimum_required( VERSION 3.0 )

project( VoIP_BaseCode )

include_directories( ${VOIP_EXT_INC_DIR} )

set( SRC main.cpp
         soundcard.cpp
         voip_application.cpp )

set( HDR soundcard.h
         voip_application.h )

# Note: the headers in ${HDR} are added only
# to display them when generating projects for
# your favorite IDE
add_executable( base_code ${SRC} ${HDR})
target_link_libraries( base_code ${VOIP_EXT_LIBS} )
