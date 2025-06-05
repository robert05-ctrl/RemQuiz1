cmake_minimum_required(VERSION 3.16)
project(Flashnotes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch dependencies
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

add_library(domain
    src/domain/note.cpp
    src/domain/flashcard.cpp
    src/domain/folder.cpp
)
target_include_directories(domain PUBLIC include)
target_link_libraries(domain nlohmann_json::nlohmann_json)

add_executable(flashnotes src/main.cpp)
target_link_libraries(flashnotes domain)

enable_testing()
file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(test_flashnotes ${TEST_SOURCES})
target_link_libraries(test_flashnotes gtest_main domain nlohmann_json::nlohmann_json)
add_test(NAME all_tests COMMAND test_flashnotes)
