# Testing for Controls Library (C++)
#
# Testing is enabled by default. To disable testing, use the 'BUILD_TESTS=OFF'
# flag.
#
# Tests use the Catch2 testing framework (https://github.com/catchorg/Catch2).
# See the individual tests for more information.

project(test_cc)

find_package(Catch2 REQUIRED)

include(CTest)

macro(ADD_TEST_FILE TEST_NAME FILE_NAME)
  add_executable(${TEST_NAME} ${FILE_NAME})
  target_link_libraries(${TEST_NAME} symctrl ${SYMENGINE_LIBRARIES})
  target_link_libraries(${TEST_NAME} Catch2::Catch2)
  add_test(${TEST_NAME} ${PROJECT_BINARY_DIR}/${TEST_NAME})
endmacro()

ADD_TEST_FILE(test_state_space test_state_space.cc)
# ADD_TEST_FILE(test_transfer_function test_transfer_function.cc)
ADD_TEST_FILE(test_analysis test_analysis.cc)
