# Controls Library

cmake_minimum_required(VERSION 3.3.2)

project(symctrl)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(CTRLLIB_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

# set_target_properties(ctrllib PROPERTIES VERSION ${CTRLLIB_VERSION})

find_package(SymEngine CONFIG REQUIRED)

include(GenerateExportHeader)
include(GNUInstallDirs)
include(ExternalProject)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

# Macro to install header files to the include directory.
macro(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    foreach(HEADER ${${HEADER_LIST}})
        string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})

        install(FILES
          ${HEADER}
          DESTINATION include/libsymctrl/${DIR}
        )

    endforeach()
endmacro()

# Macro to prepend a string to each element of a list.
macro(PREPEND NEW_VAR PREFIX)
  set(NEW_LIST "")

  foreach(FILE_NAME ${ARGN})
    list(APPEND NEW_LIST "${PREFIX}/${FILE_NAME}")
  endforeach()

  set(${NEW_VAR} "${NEW_LIST}")

endmacro()

# Project Directories
#
# List of project subdirectories to be added.
#
# When modifying this file with new subdirectories, edit this variable. The
# order of the project directories is the order the subdirectories will be
# added.
set(symctrl_INCLUDE_DIRECTORIES
  symctrl
)

# Add all subdirectories.
foreach(dir ${symctrl_INCLUDE_DIRECTORIES})
  add_subdirectory(${dir})
endforeach()

# Each CMakeLists file in the subdirectories will configure and add its own
# source files to the PROJECT_SRC list. Once all source files have been added,
# they are compiled into the shared object library.
add_library(symctrl SHARED ${PROJECT_SRC})

generate_export_header(symctrl)

target_include_directories(symctrl PUBLIC
  $<BUILD_INTERFACE:${symctrl_BINARY_DIR}>
  $<BUILD_INTERFACE:${symctrl_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(symctrl PUBLIC ${SYMENGINE_INCLUDE_DIRS})

target_link_libraries(symctrl ${SYMENGINE_LIBRARIES})

install(TARGETS symctrl
  EXPORT symctrl
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT symctrl
  FILE CtrlTargets.cmake
  NAMESPACE Control::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libsymctrl
)

install(FILES
  ${CMAKE_BINARY_DIR}/ctrl_export.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libsymctrl
)

# Matlab Support
option(BUILD_MATLAB "Build Matlab wrapper library." OFF)

if(BUILD_MATLAB)
  add_subdirectory(matlab)
  # ExternalProject_Add(ctrltbx_matlab
  #   SOURCE_DIR "${PROJECT_SOURCE_DIR}/matlab"
  #   BUILD_COMMAND make
  #   INSTALL_COMMAND make install
  #   BUILD_ALWAYS 1
  # )
endif()

# Python Support
option(BUILD_PYTHON "Build Python wrapper library." OFF)

if(BUILD_PYTHON)
  add_subdirectory(python)
  # ExternalProject_Add(ctrltbx_matlab
  #   SOURCE_DIR "${PROJECT_SOURCE_DIR}/python"
  #   BUILD_COMMAND make
  #   INSTALL_COMMAND make install
  #   BUILD_ALWAYS 1
  # )
endif()
