##########################
#    MComms Includes     #
##########################

add_subdirectory(printer)
add_subdirectory(xmlprotocol)

if (TIJ)
	add_subdirectory(tij)
	add_subdirectory(mprotocol)
endif()
if(JET)
	add_subdirectory(jet)
	add_subdirectory(jetprotocol)
endif()

add_subdirectory(nisx)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
