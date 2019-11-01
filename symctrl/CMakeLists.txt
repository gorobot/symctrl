# Source Files for Controls Library

# A list of all source files to be included in the shared library. This should
# point to files with extern "C" function definitions.
set(SRC
  # c_wrapper.cc
  # controller.cc
  math/functor/kernel.cc
  math/matrix/operations/gram.cc
  # systems/operations/controllability.cc
  # systems/operations/linearize.cc
  # systems/operations/observability.cc
  # systems/visitors/subs.cc
  # ode/euler/euler.cc
)

# A list of all header files with C header definitions.
set(HEADERS
  assert.hpp
  # c_wrapper.hpp
  kernel.hpp
  math/math.hpp
  math/expression.hpp
  math/functor.hpp
  math/functor/functor.hpp
  math/functor/kernel.hpp
  math/functor/lambda.hpp
  math/matrix.hpp
  math/matrix/block.hpp
  math/matrix/block/block.hpp
  math/matrix/constant.hpp
  math/matrix/constant/identity.hpp
  math/matrix/constant/ones.hpp
  math/matrix/constant/zeros.hpp
  math/matrix/dense.hpp
  math/matrix/dense/dense.hpp
  math/matrix/expression.hpp
  math/matrix/expression/add.hpp
  math/matrix/expression/block.hpp
  math/matrix/expression/constant.hpp
  math/matrix/expression/dense.hpp
  math/matrix/expression/inverse.hpp
  math/matrix/expression/matrix.hpp
  math/matrix/expression/mul.hpp
  math/matrix/expression/neg.hpp
  math/matrix/expression/sparse.hpp
  math/matrix/expression/static.hpp
  math/matrix/expression/sub.hpp
  math/matrix/expression/transpose.hpp
  math/matrix/expression/unary.hpp
  math/matrix/expression/vector.hpp
  math/matrix/operations.hpp
  math/matrix/operations/gram.hpp
  math/matrix/operations/jacobian.hpp
  math/matrix/operations/norm.hpp
  math/matrix/operations/trace.hpp
  math/matrix/matrix.hpp
  math/matrix/sparse.hpp
  math/matrix/sparse/sparse.hpp
  math/matrix/static.hpp
  math/matrix/static/dense.hpp
  math/matrix/static/vector.hpp
  math/matrix/traits/is_hamiltonian.hpp
  math/matrix/traits/is_lower.hpp
  math/matrix/traits/is_square.hpp
  math/matrix/traits/is_symmetric.hpp
  math/matrix/traits/is_upper.hpp
  math/matrix/type_traits/is_constant.hpp
  math/matrix/type_traits/is_dense.hpp
  math/matrix/type_traits/is_expr.hpp
  math/matrix/type_traits/is_matrix.hpp
  math/matrix/type_traits/is_static.hpp
  math/matrix/type_traits/is_vector.hpp
  math/matrix/vector.hpp
  math/matrix/vector/vector.hpp
  math/random.hpp
  math/random/random_distribution.hpp
  math/random/random_variable.hpp
  ode/ode.hpp
  shims/default.hpp
  shims/symbolic.hpp
  systems/functor/functor.hpp
  systems/hybrid/dtshs.hpp
  systems/mdp/mdp.hpp
  systems/mdp/pomdp.hpp
  systems/expression/transferfunction.hpp
  systems/operations/controllability.hpp
  systems/operations/linearize.hpp
  systems/operations/observability.hpp
  systems/statespace/statespace.hpp
  systems/traits/is_controllable.hpp
  systems/traits/is_observable.hpp
  systems/transferfunction/transferfunction.hpp
  systems/transferfunction/transfermatrix.hpp
  systems/visitors/subs.hpp
  systems/mdp.hpp
  systems/statespace.hpp
  systems/system.hpp
  systems/transferfunction.hpp
  systems/visitor.hpp
  type_traits/is_default.hpp
  type_traits/is_scalar.hpp
  type_traits/is_symbolic.hpp
)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)

prepend(CURRENT_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
prepend(CURRENT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

set(PROJECT_SRC ${PROJECT_SRC} ${CURRENT_SRC} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} ${CURRENT_HEADERS} PARENT_SCOPE)
