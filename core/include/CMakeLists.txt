##########################
#	 MComms Includes	 #
##########################

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/printersmanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/printercontroller.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/tijmonitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tijcontroller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tijviewer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tijobserver.h

    ${CMAKE_CURRENT_SOURCE_DIR}/clientmanager.h
	${CMAKE_CURRENT_SOURCE_DIR}/clientHandler.h
    PARENT_SCOPE
    )
