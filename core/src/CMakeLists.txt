##################################
#	 Printers core Sources		 #
##################################

if (${ENABLE_TESTS})
	add_subdirectory(test)
	set(SRC_TEST ${SRC_TEST}
		PARENT_SCOPE
	)
	set(HDRS_TEST ${HDRS_TEST}
		PARENT_SCOPE
	)
endif()

if (${INCLUDE_TIJ_LIBS})
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tij)
endif()
if (${INCLUDE_JET_LIBS})
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/jet)
endif()

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/printersmanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printercontroller.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/clientmanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/clientHandler.cpp
    PARENT_SCOPE
)

set(HEADERS ${HEADERS}
#   ${CMAKE_CURRENT_SOURCE_DIR}/
    PARENT_SCOPE
)
