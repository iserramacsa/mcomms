##################################
#   Jet commands Unit Tests	 	#
##################################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommandmock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommand_ut.cpp

	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommandmock.h
	PARENT_SCOPE
	)
