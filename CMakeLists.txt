CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(Memory_Manager C)


IF (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    MESSAGE(FATAL_ERROR "In-source builds are not allowed. Use: cmake -S . -B build")
ENDIF()


ADD_EXECUTABLE(example src/memory_manager.c test/example.c)

ADD_EXECUTABLE(sample1 src/memory_manager.c test/sample1.c)
ADD_EXECUTABLE(sample2 src/memory_manager.c test/sample2.c)

TARGET_INCLUDE_DIRECTORIES(example PRIVATE include)
TARGET_INCLUDE_DIRECTORIES(sample1 PRIVATE include)
TARGET_INCLUDE_DIRECTORIES(sample2 PRIVATE include)
