##########################
#	MyProject Sources	 #
##########################

if (${USE_SIGNALS})
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/signals ${PROJECT_BINARY_DIR}/signals)
	set (INCLUDES ${INCLUDES}
		${CMAKE_CURRENT_SOURCE_DIR}/signals
		)
endif()

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)

set (INCLUDES ${INCLUDES}
	PARENT_SCOPE
	)
