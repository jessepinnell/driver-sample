set(APP_NAME DriverSampleApp)
set(APP_SRCS DriverSampleApp.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(${APP_NAME} ${APP_SRCS})
target_link_libraries(${APP_NAME} MCP25625)
target_link_libraries (${APP_NAME} ${CMAKE_THREAD_LIBS_INIT})


add_build_macros(${APP_NAME})
add_g3logger(${APP_NAME})
add_lint(${APP_NAME} ${APP_SRCS})

install(TARGETS ${APP_NAME} DESTINATION bin)
