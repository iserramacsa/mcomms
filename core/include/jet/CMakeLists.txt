##########################
#	 MComms Includes	 #
##########################

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/jetmonitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/jetcontroller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/jetnotifier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/jetviewer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/jetobserver.h
    PARENT_SCOPE
    )

