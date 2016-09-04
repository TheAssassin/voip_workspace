cmake_minimum_required( VERSION 3.0 )

project( VoIP_BaseCode )

include_directories( ${VOIP_EXT_INC_DIR} )

set( SRC main.cpp
         voip_application.cpp )

set( HDR voip_application.h )

# Note: the headers in ${HDR} are added only
# to display them when generating projects for
# your favorite IDE
add_executable( base ${SRC} ${HDR})
target_link_libraries( base ${VOIP_EXT_LIBS} )
