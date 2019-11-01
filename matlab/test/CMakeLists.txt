# Testing for Controls Library (Matlab)
#
# Testing is enabled by default. To disable testing, use the 'BUILD_TESTS=OFF'
# flag.
#
# Tests use the Matlab unit testing framework.

project(test_matlab)

include(CTest)

macro(ADD_MATLAB_TEST_FILE TEST_NAME FILE_NAME)
  matlab_add_unit_test(
    NAME ${TEST_NAME}
    UNITTEST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}
    MATLAB_ADDITIONAL_STARTUP_OPTIONS -nojvm
  )
endmacro()

ADD_MATLAB_TEST_FILE(test_symctrl_matlab test_symctrl.m)
ADD_MATLAB_TEST_FILE(test_state_space_matlab test_state_space.m)
ADD_MATLAB_TEST_FILE(test_eom2statespace_matlab test_eom2statespace.m)
ADD_MATLAB_TEST_FILE(test_transfer_function_matlab test_transfer_function.m)

ADD_MATLAB_TEST_FILE(test_random_variable_matlab test_random_variable.m)

ADD_MATLAB_TEST_FILE(test_ode_matlab test_ode.m)
