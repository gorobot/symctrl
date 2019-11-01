#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/block.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/traits/is_square.hpp>
#include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/systems/operations/observability.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Observability Matrix
//
Math::BlockMatrix<symbolic_t>
observability_matrix(const Math::SymbolicDense &A,
                     const Math::SymbolicDense &C) {
  SYMCTRL_ASSERT(A.nrows() != 0);
  SYMCTRL_ASSERT(C.nrows() != 0);
  SYMCTRL_ASSERT(is_square(A));
  SYMCTRL_ASSERT(A.nrows() == C.ncols());

  size_t n_ = A.nrows();

  Math::BlockMatrix<symbolic_t> R(n_, 1);

  R[0] = C;

  for(size_t i = 1; i < n_; i++) {
    R[i] = R[i - 1] * A;
  }

  return R;
}

Math::BlockMatrix<symbolic_t> observability_matrix(const StateSpace &sys) {
  Math::SymbolicDense A = sys.A();
  Math::SymbolicDense C = sys.C();

  return observability_matrix(A, C);
}

} // Controls
