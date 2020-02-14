##########################
#	 Network Sources	 #
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
	${CMAKE_CURRENT_SOURCE_DIR}/network.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tcpsocket.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/udpsocket.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/networknode.cpp
)

set(HEADERS ${HEADERS}
)

if (UNIX OR APPLE)
	set(SOURCES ${SOURCES}
		${CMAKE_CURRENT_SOURCE_DIR}/unixsocket.cpp
		)
else()
	set(SOURCES ${SOURCES}
		${CMAKE_CURRENT_SOURCE_DIR}/winsockets.cpp
		)
endif()


set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
