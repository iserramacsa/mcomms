##########################
#	MCommsUI Sources	 #
##########################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerslistmodel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerconndialog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/networkdialog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerstatusview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerconfigview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printercommsview.cpp
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
