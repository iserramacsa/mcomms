#################################
##	Macsa Utils: Signals
#################################
cmake_minimum_required(VERSION 3.5)


set(PROJECT_NAME SignalsC11)
project(${PROJECT_NAME})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

## Include macsa common code
include(${PROJECT_SOURCE_DIR}/../../toolchain/cmake/macsa.cmake)

set(SIGNALS_VERSION_MAJOR 1)
set(SIGNALS_VERSION_MINOR 0)
set(SIGNALS_VERSION_PATCH 0)
set(SIGNALS_VERSION ${SIGNALS_VERSION_MAJOR}.${SIGNALS_VERSION_MINOR}.${SIGNALS_VERSION_PATCH})

add_definitions(-DSIGNALS_VERSION_MAJOR=${SIGNALS_VERSION_MAJOR})
add_definitions(-DSIGNALS_VERSION_MINOR=${SIGNALS_VERSION_MINOR})
add_definitions(-DSIGNALS_VERSION_PATCH=${SIGNALS_VERSION_PATCH})
add_definitions(-DSIGNALS_VERSION_STR="${SIGNALS_VERSION}")

set(SOURCES 
    #${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )

set(HEADERS 
    #${HEADERS}
    ${PROJECT_SOURCE_DIR}/signals.hpp
    )

set(INCLUDES
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

include_directories(${INCLUDES})

add_executable( ${PROJECT_NAME} ${SOURCES} ${HEADERS})
