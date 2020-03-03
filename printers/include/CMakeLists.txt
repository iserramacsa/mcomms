##########################
#    MComms Includes     #
##########################

add_subdirectory(printer)
add_subdirectory(tij)
add_subdirectory(mprotocol)
add_subdirectory(nisx)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(_HDRS ${HDRS}
	${HEADERS_LIB}
	PARENT_SCOPE
	)
