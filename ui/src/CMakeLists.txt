##########################
#	MCommsUI Sources	 #
##########################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerslistmodel.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printerconndialog.cpp
	#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui ${CMAKE_BINARY_DIR}/ui/src/designs)

set(UIS ${UIS}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
#	${CMAKE_CURRENT_SOURCE_DIR}/
	PARENT_SCOPE
	)
