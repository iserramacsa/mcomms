##################################
#   Network Sources Unit Tests	 #
##################################

set(_SRCS ${_SRCS}
	${CMAKE_CURRENT_SOURCE_DIR}/network_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/socket_moc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/abstractsocket_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/networknode_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/server_moc.cpp
	PARENT_SCOPE
	)

set(_HDRS ${_HDRS}
	${CMAKE_CURRENT_SOURCE_DIR}/socket_moc.h
	${CMAKE_CURRENT_SOURCE_DIR}/server_moc.h
	PARENT_SCOPE
	)
