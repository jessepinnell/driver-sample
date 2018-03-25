include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set_source_files_properties(driver_sample.i PROPERTIES CPLUSPLUS ON)
swig_add_library(driver_sample LANGUAGE python SOURCES driver_sample.i)
swig_link_libraries(driver_sample ${PYTHON_LIBRARIES} MCP25625)
set_source_files_properties( ${swig_generated_file_fullname}
   PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-cast-qual -Wno-shadow")
