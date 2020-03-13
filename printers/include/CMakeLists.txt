##########################
#    MComms Includes     #
##########################

add_subdirectory(printer)
add_subdirectory(xmlprotocol)
add_subdirectory(tij)
add_subdirectory(jet)
add_subdirectory(mprotocol)
add_subdirectory(jetprotocol)
add_subdirectory(nisx)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
