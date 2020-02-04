##########################
#  TIJ Printer Includes  #
##########################

set(HEADERS_LIB
	${CMAKE_CURRENT_SOURCE_DIR}tijcomms.h
	${CMAKE_CURRENT_SOURCE_DIR}/tijprinter.h
	)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(_HDRS ${HDRS}
	${HEADERS_LIB}
	PARENT_SCOPE
	)
