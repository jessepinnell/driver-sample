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

set(DRIVER_SRCS MCP25625Driver.cpp)
set(DRIVER_HEADERS MCP25625Driver.hpp)

include_directories(${CMAKE_SOURCE_DIR})
add_library(MCP25625 ${DRIVER_SRCS})
add_build_macros(MCP25625)
add_g3logger(MCP25625)
add_lint(MCP25625 ${DRIVER_SRCS} ${DRIVER_HEADERS})

# TODO(jessepinnell) add libs for SPI
target_link_libraries(MCP25625 bcm2835)
