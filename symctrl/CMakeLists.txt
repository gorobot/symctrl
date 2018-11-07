# Source Files for Controls Library

# A list of all source files to be included in the shared library. This should
# point to files with extern "C" function definitions.
set(SRC
  analysis.cc
  c_wrapper.cc
  control_model.cc
  # mdp.cc
  # mdp_train.cc
  state_space.cc
  system.cc
  # transfer_function.cc
  visitor.cc
  matrix/eig.cc
  matrix/hessenberg.cc
  matrix/house.cc
  matrix/linalg.cc
  matrix/qr.cc
  matrix/schur.cc
)

# A list of all header files with C header definitions.
set(HEADERS
  analysis.hpp
  c_wrapper.hpp
  control_model.hpp
  # mdp.hpp
  # mdp_train.hpp
  ode_sim.hpp
  state_space.hpp
  subs.hpp
  system.hpp
  # transfer_function.hpp
  visitor.hpp
  matrix/eig.hpp
  matrix/linalg.hpp
  matrix/dense.hpp
  matrix/sparse.hpp
)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)

prepend(PROJECT_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
prepend(PROJECT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

set(PROJECT_SRC ${PROJECT_SRC} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} PARENT_SCOPE)
