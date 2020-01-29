##########################
#	MCommsUI Sources	 #
##########################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/printerviewercontroller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerviewer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerstatusviewer.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/printerviewercontroller.h
	${CMAKE_CURRENT_SOURCE_DIR}/printerviewer.h
	${CMAKE_CURRENT_SOURCE_DIR}/printerstatusviewer.h
#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)

set (INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
	)
