##########################
#	 MComms Sources		 #
##########################

if (${ENABLE_TESTS})
	add_subdirectory(test)
	set(SRC_TEST ${SRC_TEST}
		PARENT_SCOPE
	)
	set(HDRS_TEST ${HDRS_TEST}
		PARENT_SCOPE
	)
endif()

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/printersmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printermonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printercontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tijprintermonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tijprintercontroller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijobserver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijnotifier.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/clientmanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/clientHandler.cpp
    PARENT_SCOPE
)

set(HEADERS ${HEADERS}
#   ${CMAKE_CURRENT_SOURCE_DIR}/
    PARENT_SCOPE
)
