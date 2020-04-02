##########################
#	 Tij Core Sources	 #
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
    ${CMAKE_CURRENT_SOURCE_DIR}/tijcontroller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tijmonitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tijviewer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijobserver.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijnotifier.cpp
    PARENT_SCOPE
)

set(HEADERS ${HEADERS}
#   ${CMAKE_CURRENT_SOURCE_DIR}/
    PARENT_SCOPE
)
