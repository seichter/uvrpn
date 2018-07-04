# vim: set sw=4 ts=8 et ic ai:

SET(VRPN_LIBRARY)

FIND_PATH( VRPN_INCLUDE_DIR "vrpn_Configure.h"
	PATHS
    $ENV{OSG_ROOT}/include
    ${LOCAL_VRPN_PATH}
	/usr/local/include
	/opt/local/include
	)

FIND_LIBRARY( VRPN_LIBRARY "vrpn"
    $ENV{OSG_ROOT}/lib
    ${LOCAL_VRPN_PATH}/pc_win32/Release
	/usr/local/lib
	/opt/local/lib
)

FIND_LIBRARY( VRPN_SERVER_LIBRARY "vrpnserver"
	$ENV{OSG_ROOT}/lib
	${LOCAL_VRPN_PATH}/pc_win32/Release
	/usr/local/lib
	/opt/local/lib
	)

FIND_LIBRARY( VRPN_LIBRARY_DEBUG "vrpn${CMAKE_DEBUG_POSTFIX}"
    $ENV{OSG_ROOT}/lib
    ${LOCAL_VRPN_PATH}/pc_win32/Debug
)

IF( NOT VRPN_LIBRARY_DEBUG )
    IF( VRPN_LIBRARY )
        SET( VRPN_LIBRARY_DEBUG VRPN_LIBRARY )
    ENDIF( VRPN_LIBRARY )
ENDIF( NOT VRPN_LIBRARY_DEBUG)
           
SET( VRPN_FOUND "NO" )
IF( VRPN_LIBRARY AND VRPN_INCLUDE_DIR )
    SET( VRPN_FOUND "YES" )
ENDIF( VRPN_LIBRARY AND VRPN_INCLUDE_DIR )
