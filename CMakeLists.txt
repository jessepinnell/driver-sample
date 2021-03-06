# MIT License
#
# Copyright (c) 2018 Jesse Pinnell
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.3)
project(driver-sample)
enable_language(CXX)
enable_testing()
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/modules")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(Threads REQUIRED)
find_package(Valgrind REQUIRED)

set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "")


# Set where the created files should go
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(g3loggerConfig)

# Bring in project-specific compiler flags, macros, etc.
include(driver-sample)

include(cpplint)
include(gtest)

find_package(SWIG 3 REQUIRED)
include(${SWIG_USE_FILE})
# if python3 is used, then the PyInit method is generated insted of init_* so a
# "ImportError: dynamic module does not define init function (init_blah) will occur"
find_package(PythonLibs 2.7 REQUIRED)
find_package(Pylint REQUIRED)

# TODO(jessepinnell) add check for wx python (causes failure in lint build step)


# TODO(jessepinnell) doxygen
# TODO(jessepinnell) cpack

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(test)
add_subdirectory(python)
