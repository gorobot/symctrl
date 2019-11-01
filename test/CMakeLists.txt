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

# ADD_TEST_FILE(test_playground2 test_playground2.cc)

ADD_TEST_FILE(test_symbolic_number test_symbolic_number.cc)
ADD_TEST_FILE(test_symbolic_variable test_symbolic_variable.cc)
ADD_TEST_FILE(test_symbolic_type test_symbolic_type.cc)
# ADD_TEST_FILE(test_symbolic_matrix test_symbolic_matrix.cc)

# ADD_TEST_FILE(test_type_traits test_type_traits.cc)
# ADD_TEST_FILE(test_function test_function.cc)
# ADD_TEST_FILE(test_kernel test_kernel.cc)
#
# ADD_TEST_FILE(test_matrix_block test_matrix_block.cc)
# ADD_TEST_FILE(test_matrix_constant test_matrix_constant.cc)
ADD_TEST_FILE(test_matrix_dense test_matrix_dense.cc)
# ADD_TEST_FILE(test_matrix_operations test_matrix_operations.cc)
# ADD_TEST_FILE(test_matrix_sparse test_matrix_sparse.cc)
ADD_TEST_FILE(test_matrix_static test_matrix_static.cc)
ADD_TEST_FILE(test_matrix_vector test_matrix_vector.cc)

# ADD_TEST_FILE(test_random_variable test_random_variable.cc)

# ADD_TEST_FILE(test_statespace test_statespace.cc)
# ADD_TEST_FILE(test_statespace_operations test_statespace_operations.cc)
# ADD_TEST_FILE(test_transferfunction test_transferfunction.cc)

# ADD_TEST_FILE(test_ode test_ode.cc)

# ADD_TEST_FILE(test_mdp test_mdp.cc)
