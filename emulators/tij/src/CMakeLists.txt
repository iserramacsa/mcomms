##########################
# TIJEmulator Sources	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui ${CMAKE_BINARY_DIR}/emulators/tij/ui/qtdesigns)
set(UIS ${UIS}
    PARENT_SCOPE
    )

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tijemulator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/emulatorwindow.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/emulatorwindow.h
#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)
