# Matlab Support for Controls Library
#
# Note that to install Matlab support, cmake must have access to a system with
# Matlab already installed.

find_package(SymEngine CONFIG REQUIRED)

set(MATLAB_ADDITIONAL_VERSIONS
    "R2018b=9.5"
    "R2018a=9.4")

find_package(Matlab MODULE REQUIRED
  COMPONENTS MAIN_PROGRAM MEX_COMPILER MX_LIBRARY
)

set(MATLAB_MINIMUM_VERSION 9.2)
set(MATLAB_MINIMUM_VERSION_NAME matlab_get_release_name_from_version())

set(MATLAB_TEMP_DIR ${CMAKE_BINARY_DIR}/Matlab)
if(NOT EXISTS "${MATLAB_TEMP_DIR}")
  file(MAKE_DIRECTORY "${MATLAB_TEMP_DIR}")
endif()

if(Matlab_VERSION_STRING VERSION_LESS ${MATLAB_MINIMUM_VERSION})
  message(FATAL_ERROR "Matlab ${MATLAB_MINIMUM_VERSION_NAME} or greater is required.")
endif()

# MATLAB_GET_USER_PATH_FROM_MATLAB_RUN
#
# Gets the user path by calling the Matlab function 'userpath' from the
# terminal.
#
# IMPORTANT: It is necessary to pause the execution of the command before
# exiting. Otherwise, it is possible to get an error claiming that there was an
# abnormal termination.
function(MATLAB_GET_USER_PATH_FROM_MATLAB_RUN MATLAB_USER_PATH)
  # Remove the temporary file if it exists.
  if(EXISTS "${MATLAB_TEMP_DIR}/matlabUserPathLog.cmaketmp")
    file(REMOVE "${MATLAB_TEMP_DIR}/matlabUserPathLog.cmaketmp")
  endif()

  if(WIN32)
    set(MATLAB_ADDITIONAL_COMMANDS "-wait")
  endif()

  set(devnull)
  if(UNIX)
    set(devnull INPUT_FILE /dev/null)
  elseif(WIN32)
    set(devnull INPUT_FILE NUL)
  endif()

  # Call the Matlab command to get the user path.
  execute_process(
    COMMAND "${Matlab_MAIN_PROGRAM}" -nosplash -nojvm ${MATLAB_ADDITIONAL_COMMANDS} -logfile "matlabUserPathLog.cmaketmp" -nodesktop -nodisplay -r "userpath, pause(1), exit"
    OUTPUT_VARIABLE MATLAB_RESULT_OUTPUT
    RESULT_VARIABLE MATLAB_RESULT_VARIABLE
    ERROR_VARIABLE MATLAB_RESULT_ERROR
    TIMEOUT 120
    WORKING_DIRECTORY "${MATLAB_TEMP_DIR}"
    ${devnull}
  )

  # Read the file.
  file(READ "${MATLAB_TEMP_DIR}/matlabUserPathLog.cmaketmp" MATLAB_USER_PATH_LOG)
  file(REMOVE "${MATLAB_TEMP_DIR}/matlabUserPathLog.cmaketmp")

  set(index -1)
  string(FIND ${MATLAB_USER_PATH_LOG} "ans" index)
  string(SUBSTRING ${MATLAB_USER_PATH_LOG} ${index} -1 SUBSTRING_ANS)

  # Find the result of the command.
  string(
    REGEX MATCH "ans[\r\n\t ]*=[\r\n\t ]*'?(.+)?'"
    current_match
    ${SUBSTRING_ANS}
  )

  # Set the variable in the parent scope.
  set(${MATLAB_USER_PATH} ${CMAKE_MATCH_1} PARENT_SCOPE)
endfunction()

# Get the Matlab user path.
if(NOT DEFINED MATLAB_USER_PATH)
  MATLAB_GET_USER_PATH_FROM_MATLAB_RUN(MATLAB_USER_PATH)
endif()

set(MATCTRL_PATH "${MATLAB_USER_PATH}/matctrl")

set(SRC
  matlab_wrapper.cc
)

# matlab_add_mex(NAME matlab_wrapper SHARED SRC ${SRC})

set(HEADERS
  matlab_wrapper.hpp
)

add_library(matctrl SHARED ${SRC})

set_target_properties(matctrl PROPERTIES PREFIX "")
set_target_properties(matctrl PROPERTIES LINKER_LANGUAGE C)

target_include_directories(matctrl PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(matctrl PUBLIC ${Matlab_INCLUDE_DIRS})
# target_include_directories(matctrl PUBLIC ${SYMENGINE_INCLUDE_DIRS})
target_include_directories(matctrl PUBLIC ${symctrl_INCLUDE_DIRECTORIES})

target_link_libraries(matctrl ${Matlab_MEX_LIBRARY})
target_link_libraries(matctrl ${Matlab_MX_LIBRARY})
# target_link_libraries(matctrl ${SYMENGINE_LIBRARIES})
target_link_libraries(matctrl symctrl)

install(TARGETS matctrl
  EXPORT matctrl
  RUNTIME DESTINATION ${MATCTRL_PATH}
  ARCHIVE DESTINATION ${MATCTRL_PATH}
  LIBRARY DESTINATION ${MATCTRL_PATH}
  INCLUDES DESTINATION ${MATCTRL_PATH}/include
)

install(FILES
  finish.m
  loadmatctrl.m
  startup.m
  unloadmatctrl.m
  DESTINATION ${MATCTRL_PATH}
)

install(DIRECTORY
  matctrl
  DESTINATION ${MATCTRL_PATH}
)

install(FILES
  ${HEADERS}
  DESTINATION ${MATCTRL_PATH}/include
)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
