##########################
#  Jet Printer Includes  #
##########################

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/jetcomms.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetprinter.h
	${CMAKE_CURRENT_SOURCE_DIR}/printhead.h
	${CMAKE_CURRENT_SOURCE_DIR}/datatypes.h
	${CMAKE_CURRENT_SOURCE_DIR}/messagemanager.h

	PARENT_SCOPE
	)
