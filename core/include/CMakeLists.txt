##########################
#	 MComms Includes	 #
##########################

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/printersmanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/printermonitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/printercontroller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tijprintermonitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tijprintercontroller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/clientmanager.h
	${CMAKE_CURRENT_SOURCE_DIR}/clientHandler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tijobserver.h
    PARENT_SCOPE
    )
