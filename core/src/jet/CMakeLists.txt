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

	${CMAKE_CURRENT_SOURCE_DIR}/jetcontroller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetmonitor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetnotifier.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetobserver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetviewer.cpp
    PARENT_SCOPE
)

set(HEADERS ${HEADERS}
#   ${CMAKE_CURRENT_SOURCE_DIR}/
    PARENT_SCOPE
)
