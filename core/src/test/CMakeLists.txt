##################################
#   Network Sources Unit Tests	 #
##################################

set(SRC_TEST ${SRC_TEST}
	${CMAKE_CURRENT_SOURCE_DIR}/clientHandler_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/clientmanager_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printercontroller_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printermonitor_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printersmanager_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijprintercontroller_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijprintermonitor_ut.cpp

	PARENT_SCOPE
	)

set(HDRS_TEST ${HDRS_TEST}
	PARENT_SCOPE
	)
