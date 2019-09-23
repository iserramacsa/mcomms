##################################
#   Network Sources Unit Tests	 #
##################################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/mcommands_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mcommandmock.cpp
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/mcommandmock.h
	PARENT_SCOPE
	)
