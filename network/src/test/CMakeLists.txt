##################################
#   Network Sources Unit Tests	 #
##################################

set(SRC_TEST ${SRC_TEST}
	${CMAKE_CURRENT_SOURCE_DIR}/network_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/abstractsocket_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/networknode_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/nodeobserver_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/socket_moc.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/server_moc.cpp
	PARENT_SCOPE
	)

set(HDRS_TEST ${HDRS_TEST}
	${CMAKE_CURRENT_SOURCE_DIR}/socket_moc.h
	${CMAKE_CURRENT_SOURCE_DIR}/server_moc.h
	PARENT_SCOPE
	)
