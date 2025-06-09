# CMake generated Testfile for 
# Source directory: C:/Users/rober/source/repos/RemQuiz1/Flashnotes
# Build directory: C:/Users/rober/source/repos/RemQuiz1/Flashnotes/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(all_tests "C:/Users/rober/source/repos/RemQuiz1/Flashnotes/out/build/x64-Debug/test_flashnotes.exe")
set_tests_properties(all_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/rober/source/repos/RemQuiz1/Flashnotes/CMakeLists.txt;74;add_test;C:/Users/rober/source/repos/RemQuiz1/Flashnotes/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
subdirs("_deps/nlohmann_json-build")
subdirs("src/gui")
