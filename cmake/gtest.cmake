include(ExternalProject)
# TODO(jessepinnell) optimize this; it tries to clone every make
set(GTEST_GIT_REPOSITORY "https://github.com/google/googletest.git")
set(GTEST_BINARY_DIR "${CMAKE_BINARY_DIR}/gtest")
set(GTEST_SOURCE_DIR "${GTEST_BINARY_DIR}/src")
set(GTEST_BUILD_DIR "${GTEST_BINARY_DIR}/build")

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


include_directories(${GTEST_SOURCE_DIR}/googletest/include)
link_directories(${GTEST_BUILD_DIR}/googletest)
set(GTEST_LIBRARY libgtest.a)
set(GTEST_MAIN_LIBRARY libgtest_main.a)
