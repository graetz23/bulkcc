# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/chda/source/bulkcc/build/_deps/acutest-src"
  "/home/chda/source/bulkcc/build/_deps/acutest-build"
  "/home/chda/source/bulkcc/build/_deps/acutest-subbuild/acutest-populate-prefix"
  "/home/chda/source/bulkcc/build/_deps/acutest-subbuild/acutest-populate-prefix/tmp"
  "/home/chda/source/bulkcc/build/_deps/acutest-subbuild/acutest-populate-prefix/src/acutest-populate-stamp"
  "/home/chda/source/bulkcc/build/_deps/acutest-subbuild/acutest-populate-prefix/src"
  "/home/chda/source/bulkcc/build/_deps/acutest-subbuild/acutest-populate-prefix/src/acutest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/chda/source/bulkcc/build/_deps/acutest-subbuild/acutest-populate-prefix/src/acutest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/chda/source/bulkcc/build/_deps/acutest-subbuild/acutest-populate-prefix/src/acutest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
