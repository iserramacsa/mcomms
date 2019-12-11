#############################################
#   Printers data structures and protocols  #
#############################################
## TIJ Printers

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tij ${CMAKE_BINARY_DIR}/printers/tij)

set(HEADERS ${HEADERS} PARENT_SCOPE)
set(SOURCES ${SOURCES} PARENT_SCOPE)
set(INCLUDES ${INCLUDES} PARENT_SCOPE)
set(EXTERNAL_LIBS ${EXTERNAL_LIBS} PARENT_SCOPE)
