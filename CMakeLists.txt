cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(
    "HealthMonitor"
    VERSION 1.0.0
    DESCRIPTION "An application to monitor the health of a human"
    LANGUAGES C
)

# Enable testing and add the tests
include(CTest)

set(CMAKE_C_STANDARD 17)

# Include the 'include' directory, where the headers are located
include_directories(include)

# To automatically download external dependencies, use 'FetchContent'
include(FetchContent)

# We are going to use Unity to download and test our program
set(UNITY_GIT_URL "https://github.com/ThrowTheSwitch/Unity.git")

# We are going to use cJSON to manipulate JSON format files
set(CJSON_GIT_URL "https://github.com/DaveGamble/cJSON.git")

# Enable debug
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
    Unity
    GIT_REPOSITORY ${UNITY_GIT_URL}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/Unity
    UPDATE_COMMAND "" # Disable the update command
)

FetchContent_Declare(
    cJSON
    GIT_REPOSITORY ${CJSON_GIT_URL}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/cJSON
    UPDATE_COMMAND "" # Disable the update command
)

# Ensure that the named dependencies have been populated
FetchContent_MakeAvailable(Unity cJSON)

# Collect all source files in src directory
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# Create the executable for the application
add_executable(${PROJECT_NAME}_application ${SRC_FILES})

# Link the cJSON library to the application
target_link_libraries(${PROJECT_NAME}_application cjson)

# Add cJSON library include directories
target_include_directories(${PROJECT_NAME}_application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/cJSON ) 

# Add subdirectory of tests if needed
if(RUN_TESTS OR RUN_COVERAGE)
    add_subdirectory(tests)
endif()
