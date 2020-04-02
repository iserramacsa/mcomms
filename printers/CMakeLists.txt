#############################################
#   Printers data structures and protocols  #
#############################################
## tij Printers

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tij ${CMAKE_BINARY_DIR}/printers/tij)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/jet ${CMAKE_BINARY_DIR}/printers/jet)

# set(HEADERS ${HEADERS} PARENT_SCOPE)
# set(SOURCES ${SOURCES} PARENT_SCOPE)
# set(INCLUDES ${INCLUDES} PARENT_SCOPE)
# set(EXTERNAL_LIBS ${EXTERNAL_LIBS} PARENT_SCOPE)
