

include_directories(${VRPN_INCLUDE_DIR})

set(uvrpn_srcs
	uvrpn_base.cpp
	uvrpn_exports.hpp
	)

add_library(uvrpn MODULE ${uvrpn_srcs})


target_link_libraries(uvrpn ${VRPN_LIBRARY})


# set prefix to nothing on all platforms
set_target_properties(uvrpn
	    PROPERTIES
		PREFIX ""
		)

# on OSX we need to use the .bundle extension
if (APPLE)
	set_target_properties(uvrpn
		    PROPERTIES
			SUFFIX ".bundle"
			)
endif()


# always install the plugin into the plugin folder
add_custom_command(TARGET uvrpn POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:uvrpn> ${CMAKE_SOURCE_DIR}/uvrpn/Assets/Plugins
		COMMENT "Copying Unity plugin to plugins directory"
		)
