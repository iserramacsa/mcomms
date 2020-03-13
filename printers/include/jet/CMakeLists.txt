##########################
#  Jet Printer Includes  #
##########################

set(HEADERS_LIB
	${CMAKE_CURRENT_SOURCE_DIR}/jetcomms.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetprinter.h
	)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(_HDRS ${HDRS}
	${HEADERS_LIB}
	PARENT_SCOPE
	)
