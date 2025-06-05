cmake_minimum_required(VERSION 3.16)
project(Flashnotes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(flashnotes src/main.cpp)

enable_testing()
add_executable(test_flashnotes tests/smoke.cpp)
target_link_libraries(test_flashnotes gtest_main)
add_test(NAME smoke COMMAND test_flashnotes)
