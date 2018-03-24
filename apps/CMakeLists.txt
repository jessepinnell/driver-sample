set(APP_NAME DriverSampleApp)
set(APP_SRCS DriverSampleApp.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(${APP_NAME} ${APP_SRCS})
target_link_libraries(${APP_NAME} MCP25625)

add_lint(${APP_NAME} ${APP_SRCS})

install(TARGETS ${APP_NAME} DESTINATION bin)
