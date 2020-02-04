##########################
#	 MComms Sources		 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()


set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/printersmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printermonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/printercontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tijprintermonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tijprintercontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clientmanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clientHandler.cpp
    PARENT_SCOPE
)

set(HEADERS ${HEADERS}
#   ${CMAKE_CURRENT_SOURCE_DIR}/
    PARENT_SCOPE
)
