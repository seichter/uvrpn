# vim: set sw=4 ts=8 et ic ai:

set(VRPN_SEARCH_PATHS
	$ENV{VRPN_ROOT}
    ${LOCAL_VRPN_PATH}
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
	)

find_path( VRPN_INCLUDE_DIR "vrpn_Configure.h"
	PATHS
	${VRPN_SEARCH_PATHS}
	PATH_SUFFIXES 
	include
	)

find_library( VRPN_vrpn_LIBRARY "vrpn"
    PATHS
	${VRPN_SEARCH_PATHS}
	PATH_SUFFIXES lib lib64
	)

find_library( VRPN_quat_LIBRARY "quat"
    PATHS
	${VRPN_SEARCH_PATHS}
	PATH_SUFFIXES lib lib64
	)

find_library( VRPN_gpsnmea_LIBRARY "gpsnmea"
    PATHS
	${VRPN_SEARCH_PATHS}
	PATH_SUFFIXES lib lib64
	)
	
set(VRPN_INCLUDE_DIRS ${VRPN_INCLUDE_DIR})
set(VRPN_LIBRARIES
	${VRPN_vrpn_LIBRARY}
	${VRPN_quat_LIBRARY}
	${VRPN_gpsnmea_LIBRARY}
	)

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set UEYE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(VRPN DEFAULT_MSG VRPN_LIBRARIES VRPN_INCLUDE_DIRS)

mark_as_advanced(VRPN_LIBRARIES VRPN_INCLUDE_DIRS)

