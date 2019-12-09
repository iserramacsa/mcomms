##########################
#    MComms Includes     #
##########################

file(GLOB HEADERS_LIB ${CMAKE_CURRENT_SOURCE_DIR}/*/*.h)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(_HDRS ${HDRS}
	${HEADERS_LIB}
	PARENT_SCOPE
	)
