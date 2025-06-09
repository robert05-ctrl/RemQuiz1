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
note titles and now includes **New**, **Save**, and **Open** buttons so you can
create fresh notes, store them to disk, and open the file from its saved
location.
