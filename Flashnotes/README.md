# Flashnotes

This is a minimal C++17 project using CMake and GoogleTest.

## Build

```bash
cmake -B build -S .
cmake --build build
```

## Run

Run the application:

```bash
./build/flashnotes
```

Run the tests:

```bash
cd build && ctest
```

### Optional WinForms GUI

When using Visual Studio on Windows (MSVC), CMake also builds a `FlashnotesGUI`
target providing a minimalist WinForms interface that links against the
controllers.

Saved notes are persisted to `notes.json` under `%APPDATA%/Flashnotes` (or
`data/notes.json` when the variable isn't set). The Notes editor lists the saved
note titles and now includes **New**, **Save**, **Open**, **Update**, and
**Delete** buttons. Selecting a note loads it for editing; the buttons are
arranged in a single row to save space.

Flashcard sets can also be managed in the GUI. The **Edit Card Sets** screen lets
you create a set, open an existing one, update it, or delete it. Individual
cards may be added or removed in a table of front/back text. The **Practice
Cards** screen allows choosing a set and flipping through its cards.
