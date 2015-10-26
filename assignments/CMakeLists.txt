cmake_minimum_required( VERSION 3.0 )

project( VoIP_Assignments )

# Base code for demonstration and reuse
add_subdirectory( base )

# Add your assignment directories here
# add_subdirectory( a1 )
# add_subdirectory( a2 )
# ...

# Solutions - this is only for your teacher :-)
if( ${VOIP_BUILD_SOLUTIONS} )
  add_subdirectory( a1_solution )
endif()
