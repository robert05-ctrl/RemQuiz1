if(NOT MSVC)
    return()
endif()

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


# Explicitly add /clr for MSVC and disable /RTC1 which conflicts with /clr
target_compile_options(FlashnotesGUI PRIVATE
    /clr
    $<$<CONFIG:Debug>:/RTC->
)
