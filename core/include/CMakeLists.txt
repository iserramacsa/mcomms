##########################
#	 MComms Includes	 #
##########################

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

if (${INCLUDE_TIJ_LIBS})
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tij)
endif()
if (${INCLUDE_JET_LIBS})
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/jet)
endif()

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/printersmanager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/printercontroller.h

    ${CMAKE_CURRENT_SOURCE_DIR}/clientmanager.h
	${CMAKE_CURRENT_SOURCE_DIR}/clientHandler.h
    PARENT_SCOPE
    )

