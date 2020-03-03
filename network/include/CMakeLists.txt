##########################
#	 Library includes	 #
##########################

#if (UNIX OR APPLE)
#	set(_HDRS ${_HDRS}
#		${CMAKE_CURRENT_SOURCE_DIR}/network/unixsocket.h
#		)
#else()
#	set(_HDRS ${_HDRS}
#		${CMAKE_CURRENT_SOURCE_DIR}/network/winsockets.h
#		)
#endif()

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/network/isocket.h
	${CMAKE_CURRENT_SOURCE_DIR}/network/network.h
	${CMAKE_CURRENT_SOURCE_DIR}/network/networkobserver.h
	${CMAKE_CURRENT_SOURCE_DIR}/network/networknotifier.h
	${CMAKE_CURRENT_SOURCE_DIR}/network/networknode.h
	${CMAKE_CURRENT_SOURCE_DIR}/network/nodeobserver.h
	${CMAKE_CURRENT_SOURCE_DIR}/network/nodenotifier.h
#	${CMAKE_CURRENT_SOURCE_DIR}/network/tcpsocket.h
#	${CMAKE_CURRENT_SOURCE_DIR}/network/udpsocket.h
#	${CMAKE_CURRENT_SOURCE_DIR}/network/abstractsocket.h
	PARENT_SCOPE
)

