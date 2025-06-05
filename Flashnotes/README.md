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
