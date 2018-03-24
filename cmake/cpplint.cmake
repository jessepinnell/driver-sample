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

set(CPPLINT_EXECUTABLE "python") # TODO(jessepinnell) python3 causes a no-error returning -1
set(CPPLINT_SCRIPT "${CMAKE_SOURCE_DIR}/scripts/cpplint.py")

set(VERBOSITY --verbose=1)
set(STYLE_FILTER --linelength=120)
set(STYLE_FILTER ${STYLE_FILTER} --extensions=hpp,cpp)
set(STYLE_FILTER ${STYLE_FILTER} --filter=)
set(STYLE_FILTER ${STYLE_FILTER}-whitespace/newline,)
# cpplint wants { on split lines, {} on same indent is nicer
set(STYLE_FILTER ${STYLE_FILTER}-whitespace/braces,)
# cpplint wants 2-space indent, 3 is nicer
set(STYLE_FILTER ${STYLE_FILTER}-whitespace/indent,)
set(STYLE_FILTER ${STYLE_FILTER}-runtime/references,)
set(STYLE_FILTER ${STYLE_FILTER}-build/c++14,)

function(add_lint target)
   # Create commands var to append
   set(CPPLINT_COMMANDS)

   # Add a command for each file in list
   foreach(SOURCE_FILE ${ARGN})
      get_filename_component(SOURCEFILE_ABS ${SOURCE_FILE} ABSOLUTE)
      list(APPEND CPPLINT_COMMANDS
         COMMAND ${CPPLINT_EXECUTABLE} ${CPPLINT_SCRIPT} ${STYLE_FILTER} ${VERBOSITY} ${SOURCEFILE_ABS})
   endforeach()

   add_custom_command(TARGET ${target} PRE_LINK COMMAND ${CPPLINT_COMMANDS} VERBATIM)
endfunction()
