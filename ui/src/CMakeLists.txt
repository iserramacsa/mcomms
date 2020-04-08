##########################
#	MCommsUI Sources	 #
##########################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerslistmodel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerconndialog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/networkdialog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetstatusview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijstatusview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijconfigview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijcommsview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/tijmessageselector.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerfilesview.cpp
	#	${CMAKE_CURRENT_SOURCE_DIR}/
	)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui ${CMAKE_BINARY_DIR}/ui/qtdesigns)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/viewers ${CMAKE_BINARY_DIR}/ui/viewers)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
)

set(UIS ${UIS}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)

set (INCLUDES ${INCLUDES}
	#${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
	)
