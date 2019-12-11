####################################
#   Nisx source and headers files  #
####################################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(LABELS_SOURCES ${LABELS_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/datetime.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/counter.cpp
	PARENT_SCOPE
)

set(LABELS_HEADERS ${LABELS_HEADERS}
	PARENT_SCOPE
)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)




