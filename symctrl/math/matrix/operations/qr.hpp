#ifndef SYMCTRL_MATH_MATRIX_OPERATIONS_QR_HPP
#define SYMCTRL_MATH_MATRIX_OPERATIONS_QR_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/vector.hpp>
#include <symctrl/math/matrix/operations/norm.hpp>
// #include <symctrl/math/matrix/operations/house.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// QR Decomposition (Gram-Schmidt)
//
template<typename T>
inline void qr(const DenseMatrix<T> &A, DenseMatrix<T> &Q, DenseMatrix<T> &R) {
  size_t n_ = A.nrows();
  size_t m_ = A.ncols();
  SYMCTRL_ASSERT(n_ == Q.nrows());
  SYMCTRL_ASSERT(m_ == Q.ncols());
  SYMCTRL_ASSERT(n_ == R.nrows());
  SYMCTRL_ASSERT(m_ == R.ncols());

  Vector<T> v(n_);

  for(size_t j = 0; j < m_; j++) {
    v = A.col(j);

    for(size_t i = 0; i < j; i++) {
      R(i, j) = transpose(Q.col(i)) * A.col(j);
      v -= R(i, j) * Q.col(i);
    }

    R(j, j) = norm(v);

    for(size_t k = 0; k < m_; k++) {
      Q(k, j) = v[k] / R(j, j);
    }
  }
}

// ----------------------------------------------------------------------
// QR Decomposition (Householder Reflectors)
//

// ----------------------------------------------------------------------
// QR Decomposition (Givens Rotations)
//


} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_OPERATIONS_QR_HPP
