CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(Memory_Manager C)


IF (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    MESSAGE(FATAL_ERROR "In-source builds are not allowed. Use: cmake -S . -B build")
ENDIF()


ADD_EXECUTABLE(example src/src.c test/test_client.c)
TARGET_INCLUDE_DIRECTORIES(example PRIVATE include)
