cmake_minimum_required(VERSION 2.8.5)

project(LoadBalance CXX)

include(charm)

add_library(LoadBalance
            CommMap.C
            LinearMap.C
            UnsMeshMap.C
)

addCharmModule( "linearmap" "LoadBalance" )
addCharmModule( "unsmeshmap" "LoadBalance" )

set_target_properties(LoadBalance PROPERTIES
                      LIBRARY_OUTPUT_NAME quinoa_loadbalance)

INSTALL(TARGETS LoadBalance
  	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
  	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
 	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
)
