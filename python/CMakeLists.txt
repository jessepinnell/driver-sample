include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_source_files_properties(py_driver_sample.i PROPERTIES CPLUSPLUS ON)

#3.0 swig_add_library(py_driver_sample LANGUAGE python SOURCES py_driver_sample.i)
swig_add_module(py_driver_sample python py_driver_sample.i)

# XXX a missing definition of a method declared in the class interface will cause a segfault when this is imported
swig_link_libraries(py_driver_sample ${PYTHON_LIBRARIES} MCP25625)
set_source_files_properties( ${swig_generated_file_fullname}
   PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-cast-qual -Wno-shadow -Wno-register")
add_g3logger(_py_driver_sample)

set(PYLINT pylint -d wrong-import-position -f colorized --rcfile=${CMAKE_SOURCE_DIR}/python/.pylintrc)
add_custom_command(TARGET _py_driver_sample COMMAND ${PYLINT} ${CMAKE_SOURCE_DIR}/python/driver_sample_app.py VERBATIM)

add_custom_target(copy_python_scripts)
add_custom_command(
   TARGET copy_python_scripts PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/python
   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/python ${CMAKE_BINARY_DIR}/python)
add_dependencies(_py_driver_sample copy_python_scripts)
