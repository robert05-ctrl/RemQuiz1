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

add_library(utils
    src/utils/Logger.cpp
)
target_include_directories(utils PUBLIC include)

add_library(services
    src/services/JsonPersistenceService.cpp
    src/services/NotesService.cpp
    src/services/FileService.cpp
    src/services/FlashcardService.cpp
)
target_include_directories(services PUBLIC include)
target_link_libraries(services domain utils nlohmann_json::nlohmann_json)
# build the services library with UNIT_TEST enabled but do not
# propagate the definition to consumers so production targets
# remain clean of test hooks
target_compile_definitions(services PRIVATE UNIT_TEST)

add_library(controllers
    src/controllers/AppController.cpp
    src/controllers/NotesController.cpp
    src/controllers/FileController.cpp
    src/controllers/FlashcardController.cpp
)
target_include_directories(controllers PUBLIC include)
target_link_libraries(controllers services)

if(MSVC)
    add_subdirectory(src/gui)
endif()

add_executable(flashnotes src/main.cpp)
target_link_libraries(flashnotes controllers domain utils services)

enable_testing()
file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(test_flashnotes ${TEST_SOURCES})
target_link_libraries(test_flashnotes gtest_main controllers domain utils services nlohmann_json::nlohmann_json)
# test sources rely on helper hooks enabled by the UNIT_TEST
# definition in the services library
target_compile_definitions(test_flashnotes PRIVATE UNIT_TEST)
add_test(NAME all_tests COMMAND test_flashnotes)
