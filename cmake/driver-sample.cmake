# C++ flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-format-attribute")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnormalized=id")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmaybe-uninitialized")

# valgrind flags
set(DRIVER_SAMPLE_MEMTEST_COMMAND "valgrind")
set(DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS "${DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS} -v")
set(DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS "${DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS} --tool=memcheck")
set(DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS "${DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS} --leak-check=yes")
set(DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS "${DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS} --show-reachable=no")
set(DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS "${DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS} --num-callers=20")
set(DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS "${DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS} --track-fds=yes")
set(DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS "${DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS} --xml=yes")
set(DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS "${DRIVER_SAMPLE_MEMTEST_COMMAND_OPTIONS} --error-exitcode=1")

# declare macros for making revision available to binaries
function (add_build_macros target)
   SET(src_dir ${CMAKE_SOURCE_DIR})
   target_compile_definitions(${target} PRIVATE
      DRIVER_SAMPLE_BUILD_TARGET_NAME=\"${target}\")

   execute_process(
      COMMAND uname -r
      OUTPUT_VARIABLE DRIVER_SAMPLE_BUILD_KERNEL_RELEASE
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
   target_compile_definitions(${target} PRIVATE
      DRIVER_SAMPLE_BUILD_KERNEL_RELEASE=\"${DRIVER_SAMPLE_BUILD_KERNEL_RELEASE}\")

   # TODO(jessepinnell) this is the cmake build time; will not update on subsequent makes
   execute_process(
      COMMAND date +%T_%D
      OUTPUT_VARIABLE DRIVER_SAMPLE_BUILD_TIME
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
   target_compile_definitions(${target} PRIVATE
      DRIVER_SAMPLE_BUILD_TIME=\"${DRIVER_SAMPLE_BUILD_TIME}\")

   execute_process(
      COMMAND hostname
      OUTPUT_VARIABLE DRIVER_SAMPLE_BUILD_HOST
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
   target_compile_definitions(${target} PRIVATE
      DRIVER_SAMPLE_BUILD_HOST=\"${DRIVER_SAMPLE_BUILD_HOST}\")

   execute_process(
      COMMAND git -C ${CMAKE_SOURCE_DIR} log -1 --pretty=format:%H
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      OUTPUT_VARIABLE DRIVER_SAMPLE_BUILD_GIT_REVISION
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )
   string(SUBSTRING ${DRIVER_SAMPLE_BUILD_GIT_REVISION} 0 7 DRIVER_SAMPLE_BUILD_GIT_REVISION)
   target_compile_definitions(${target} PRIVATE
      DRIVER_SAMPLE_BUILD_GIT_REVISION=\"${DRIVER_SAMPLE_BUILD_GIT_REVISION}\")
endfunction()

function(add_g3logger target)
   if (${G3LOG_FOUND})
      target_compile_definitions(${target} PRIVATE G3LOG_FOUND)
      target_link_libraries(${target} g3logger)
   else()
      message(FATAL_ERROR "g3log is not installed")
   endif()
endfunction()

function(add_to_test target_name executable)
   add_dependencies(${executable} project_googletest)
   set_target_properties(${executable} PROPERTIES SKIP_BUILD_RPATH FALSE)
   add_test(NAME ${target_name}.${executable} WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMAND ${executable})
endfunction()
