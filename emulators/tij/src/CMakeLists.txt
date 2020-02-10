##########################
# TIJEmulator Sources	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()


set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tijemulator.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)
