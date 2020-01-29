##########################################
##	Macsa Communications library
##########################################
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME MCommsUI)
project(${PROJECT_NAME})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

## Include macsa common code
include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchain/cmake/macsa.cmake)


if (WIN32)
	message("Windows version")
elseif(UNIX)
	set(EXTERNAL_LIBS -lpthread)
endif()

set(UI_VERSION_MAJOR 1)
set(UI_VERSION_MINOR 0)
set(UI_VERSION_PATCH 0)
set(UI_VERSION ${UI_VERSION_MAJOR}.${UI_VERSION_MINOR}.${UI_VERSION_PATCH})

add_definitions(-DUI_VERSION_MAJOR=${UI_VERSION_MAJOR})
add_definitions(-DUI_VERSION_MINOR=${UI_VERSION_MINOR})
add_definitions(-DUI_VERSION_PATCH=${UI_VERSION_PATCH})
add_definitions(-DUI_VERSION_STR="${UI_VERSION}")

set(SOURCES)
set(HEADERS)
set(INCLUDES)
set(UIS)
set(RESOURCES)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/ui/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/ui/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/../core ${CMAKE_BINARY_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/ui/resources)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})
set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/../core/include
	${PROJECT_SOURCE_DIR}/../network/include
	${PROJECT_SOURCE_DIR}/../printers/include
	${PROJECT_SOURCE_DIR}/../printers/tij/include
	${LIB_PREFIX}/include
)

include_directories(${INCLUDES})

# Next lines needed for building all Qt projects
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories( ${CMAKE_BINARY_DIR} )


# using Qt meta-system (precompiler)
QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${HEADERS} )

###########################
## Install targets
###########################

link_directories(
	${CMAKE_BINARY_DIR}/core
	${CMAKE_BINARY_DIR}/network
	${CMAKE_BINARY_DIR}/printers/tij
	)

# compile
if (WIN32)
	add_executable( ${PROJECT_NAME} WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
elseif(UNIX)
	add_executable( ${PROJECT_NAME} ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
endif()
# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} MComms MNetwork TijLibrary)
