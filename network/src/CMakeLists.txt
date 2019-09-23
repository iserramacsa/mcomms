##########################
#	 Network _SRCS	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(_SRCS ${_SRCS}
	${CMAKE_CURRENT_SOURCE_DIR}/network.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tcpsocket.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/udpsocket.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/networknode.cpp
)

set(_HDRS ${_HDRS}
)

if (UNIX OR APPLE)
	set(_SRCS ${_SRCS}
		${CMAKE_CURRENT_SOURCE_DIR}/unixsocket.cpp
		)
else()
	set(_SRCS ${_SRCS}
		${CMAKE_CURRENT_SOURCE_DIR}/winsockets.cpp
		)
endif()


set(_SRCS ${_SRCS}
	PARENT_SCOPE
	)

set(_HDRS ${_HDRS}
	PARENT_SCOPE
	)
