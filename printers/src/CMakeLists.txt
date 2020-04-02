##########################
#	 Printer Sources	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(PRINTERS_SOURCES ${PRINTERS_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/board.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/datecodes.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/files.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/inputs.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/iobase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/outputs.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/shotmode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/comms.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/encoder.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/cartridge.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/errors.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/messagemanager.cpp

	PARENT_SCOPE
)

set(PRINTERS_HEADERS ${PRINTERS_HEADERS}
	PARENT_SCOPE
	)

set(SOURCES ${SOURCES}
	PARENT_SCOPE)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
