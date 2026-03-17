# CMake generated Testfile for 
# Source directory: /home/chda/source/opencode/bulkcc
# Build directory: /home/chda/source/opencode/bulkcc/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(bulkcc_tests "/home/chda/source/opencode/bulkcc/build/bulkcc_tests")
set_tests_properties(bulkcc_tests PROPERTIES  _BACKTRACE_TRIPLES "/home/chda/source/opencode/bulkcc/CMakeLists.txt;57;add_test;/home/chda/source/opencode/bulkcc/CMakeLists.txt;0;")
subdirs("_deps/catch2-build")
