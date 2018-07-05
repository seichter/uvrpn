include_directories(${VRPN_INCLUDE_DIRS})

set(uvrpn_srcs
	uvrpn_base.cpp
	uvrpn_analog.cpp
	uvrpn_tracker.cpp
	uvrpn_exports.hpp
	${CMAKE_SOURCE_DIR}/README.md
	${CMAKE_SOURCE_DIR}/License.md
	)

add_library(uvrpn SHARED ${uvrpn_srcs})

target_link_libraries(uvrpn ${VRPN_LIBRARIES})

# set prefix to nothing on all platforms
set_target_properties(uvrpn
	PROPERTIES
	PREFIX ""
	)

# on OSX we need to use the .bundle extension and use the correct ABI
if (APPLE)
	set_target_properties(uvrpn
		PROPERTIES
		SUFFIX ".bundle"
		LINK_FLAGS "-stdlib=libc++ -lc++abi"
		)
endif()

# check on Windows 
if (WIN32 OR MINGW)
	set_target_properties(uvrpn
	PROPERTIES
	LINK_FLAGS "-static -static-libgcc -static-libstdc++"
	SUFFIX ".dll"
	)	
	target_link_libraries(uvrpn
	WSOCK32
	)
endif()

# always install the plugin into the plugin folder
add_custom_command(TARGET uvrpn POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:uvrpn> ${CMAKE_SOURCE_DIR}/uvrpn/Assets/Plugins
	COMMENT "copying Unity plugin to plugins directory"
	)
