# Python Support for Controls Library
#
# Note that to install python support, cmake must have access to a system with
# python already installed.

find_package(SymEngine CONFIG REQUIRED)

find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
find_package(Cython REQUIRED)

# ----------------------------------------------------------------------
# Configure Python
#
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${PYTHON_INCLUDE_DIRS})

if(NOT DEFINED PYTHON_SITE_PACKAGES)
  execute_process(
    COMMAND python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
    OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

if(NOT DEFINED PYTHON_INCLUDE_DIR)
	execute_process(
		COMMAND python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc(plat_specific=1))"
		OUTPUT_VARIABLE PYTHON_INCLUDE_DIR
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif()

set(PYCTRL_PATH ${PYTHON_SITE_PACKAGES}/pyctrl)

set(SYMENGINE_PATH ${PYTHON_SITE_PACKAGES}/symengine)
set(SYMENGINE_LIB_PATH ${SYMENGINE_PATH}/lib)

#
# # A list of all source files to be included in the shared library.
# set(SRC
#   py_wrapper.cc
# )
#
# # A list of all header files with C header definitions.
# set(HEADERS
#   py_wrapper.hpp
# )
#
# # message("After ${SRC}")
#
# add_library(pyctrl_wrapper SHARED ${SRC})
#
# target_link_libraries(pyctrl_wrapper ${LIBS})
# target_link_libraries(pyctrl_wrapper ${PYTHON_LIBRARIES})

set(CYTHON_INCLUDE_DIRECTORIES ${SYMENGINE_LIB_PATH})

cython_compile_pyx(pyctrl ${SYMENGINE_LIB_PATH})

set(SRC
  pyctrl.cc
)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU|Clang)
  set_source_files_properties(
    ${SRC}
    PROPERTIES COMPILE_FLAGS "-fno-strict-aliasing -Wno-unused-function"
  )
endif()

add_library(pyctrl SHARED ${SRC})

set_target_properties(pyctrl PROPERTIES PREFIX "")
set_target_properties(pyctrl PROPERTIES LINKER_LANGUAGE C)

target_include_directories(pyctrl PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

target_include_directories(pyctrl PUBLIC ${SYMENGINE_LIB_PATH})
target_include_directories(pyctrl PUBLIC ${symctrl_INCLUDE_DIRECTORIES})

target_link_libraries(pyctrl ${PYTHON_LIBRARIES})
target_link_libraries(pyctrl ${SYMENGINE_LIBRARIES})
target_link_libraries(pyctrl symctrl)

install(TARGETS pyctrl
  RUNTIME DESTINATION ${PYCTRL_PATH}
  ARCHIVE DESTINATION ${PYCTRL_PATH}
  LIBRARY DESTINATION ${PYCTRL_PATH}
  INCLUDES DESTINATION ${PYCTRL_PATH}/include
)

install(FILES
  __init__.py
  pyctrl.pxd
  DESTINATION ${PYCTRL_PATH}
)

# add_custom_command(
#   TARGET pyctrl
#   COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/setup.py install
#   COMMENT "Installing pyctrl."
# )
