cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Include headers project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Collect tests
file(GLOB TESTS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/unit/*.c)

# Get all source files excluding main.c
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c)
list(FILTER SRC_FILES EXCLUDE REGEX ".*main\\.c")

# Coverage
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fprofile-arcs -ftest-coverage --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")

# Create test executable
add_executable(test_${PROJECT_NAME} ${TESTS_FILES} ${SRC_FILES})

# Link with libraries
target_link_libraries(test_${PROJECT_NAME} unity cjson)

target_include_directories(test_${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/cJSON)

# Add test
add_test(NAME test_${PROJECT_NAME} COMMAND test_${PROJECT_NAME})
