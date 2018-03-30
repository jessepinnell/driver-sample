include(ExternalProject)
set(GTEST_GIT_REPOSITORY "https://github.com/google/googletest.git")
set(GTEST_BINARY_DIR "${CMAKE_BINARY_DIR}/gtest")
set(GTEST_SOURCE_DIR "${GTEST_BINARY_DIR}/src")
set(GTEST_BUILD_DIR "${GTEST_BINARY_DIR}/build")
set(GTEST_LIBRARY libgtest.a)
set(GTEST_MAIN_LIBRARY libgtest_main.a)

# This quick-and-dirty check just skips the clone if the two libraries exist already,
# otherwise the build will fail if the network is down
if (EXISTS ${GTEST_BUILD_DIR}/googletest/${GTEST_LIBRARY} AND EXISTS ${GTEST_BUILD_DIR}/googletest/${GTEST_MAIN_LIBRARY})
   add_custom_target(project_googletest ${CMAKE_COMMAND} -E echo "Google Test is already built, skipping clone")
else()
   message(STATUS "Google Test is not yet built, cloning and building...")
   ExternalProject_Add(project_googletest
      GIT_REPOSITORY ${GTEST_GIT_REPOSITORY}
      SOURCE_DIR     ${GTEST_SOURCE_DIR}
      PREFIX         ${GTEST_BINARY_DIR}
      TMP_DIR        ${GTEST_BINARY_DIR}/tmp
      STAMP_DIR      ${GTEST_BINARY_DIR}/stamp
      DOWNLOAD_DIR   ${GTEST_BINARY_DIR}/download
      BINARY_DIR     ${GTEST_BUILD_DIR}
      INSTALL_DIR    ${GTEST_BINARY_DIR}/install
      CMAKE_ARGS -DBUILD_GTEST=ON -DBUILD_GMOCK=OFF
      INSTALL_COMMAND ""
      LOG_DOWNLOAD ON
      LOG_CONFIGURE ON
      LOG_BUILD ON)
endif()

include_directories(${GTEST_SOURCE_DIR}/googletest/include)
link_directories(${GTEST_BUILD_DIR}/googletest)
