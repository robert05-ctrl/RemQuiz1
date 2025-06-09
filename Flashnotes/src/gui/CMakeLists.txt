if(NOT MSVC)
    return()
endif()

# Remove default /RTC1 runtime checks and /EHsc which conflict with /clr
foreach(flag_var
    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    string(REPLACE "/RTC1" "" ${flag_var} "${${flag_var}}")
    string(REPLACE "/EHsc" "" ${flag_var} "${${flag_var}}")
endforeach()

set(SOURCES
    Program.cpp
    MainWindow.cpp
    NoteEditorForm.cpp
    FileManagerForm.cpp
    FlashcardPracticeForm.cpp
)

add_executable(FlashnotesGUI WIN32 ${SOURCES})

# Include headers from parent project
target_include_directories(FlashnotesGUI PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link against core libraries
target_link_libraries(FlashnotesGUI PRIVATE controllers services domain utils)

# Enable C++/CLI
set_target_properties(FlashnotesGUI PROPERTIES
    COMMON_LANGUAGE_RUNTIME ""
)
set_target_properties(FlashnotesGUI PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

# Explicitly add /clr and enable asynchronous exceptions with /EHa
target_compile_options(FlashnotesGUI PRIVATE "/clr" "/EHa")
