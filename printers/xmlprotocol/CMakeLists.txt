##########################
#	 Protocol Sources	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/xmlcommands.cpp
	PARENT_SCOPE
)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
