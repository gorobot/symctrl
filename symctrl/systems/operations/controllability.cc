#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/block.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/traits/is_square.hpp>
#include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/systems/operations/controllability.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Controllability
//
Math::BlockMatrix<symbolic_t>
controllability_matrix(const Math::SymbolicDense &A,
                       const Math::SymbolicDense &B) {
  SYMCTRL_ASSERT(A.nrows() != 0);
  SYMCTRL_ASSERT(B.ncols() != 0);
  SYMCTRL_ASSERT(is_square(A));
  SYMCTRL_ASSERT(A.nrows() == B.nrows());

  size_t n_ = A.nrows();

  Math::BlockMatrix<symbolic_t> R(1, n_);

  R[0] = B;

  for(size_t i = 1; i < n_; i++) {
    R[i] = A * R[i - 1];
  }

  return R;
}

Math::BlockMatrix<symbolic_t> controllability_matrix(const StateSpace &sys) {
  Math::SymbolicDense A = sys.A();
  Math::SymbolicDense B = sys.B();

  return controllability_matrix(A, B);
}

} // Controls
