#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_MATRIX_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_MATRIX_HPP

#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Assignment Functions
//
template<typename D1, typename D2>
inline void apply_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply(~rhs);
}

template<typename D1, typename D2>
inline void apply_add_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_add(~rhs);
}

template<typename D1, typename D2>
inline void apply_sub_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_sub(~rhs);
}

template<typename D1, typename D2>
inline void apply_mul_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_mul(~rhs);
}

template<typename D1, typename D2>
inline void apply_inverse_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_inverse(~rhs);
}

template<typename D1, typename D2>
inline void apply_transpose_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_transpose(~rhs);
}

// ----------------------------------------------------------------------
// Matrix Equal
//
template<typename D1, typename D2>
inline bool equal(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return (std::is_same<D1, D2>::value &&
          reinterpret_cast<const void *>(&lhs) ==
          reinterpret_cast<const void *>(&rhs));
}

template<typename T>
inline bool equal(const T lhs, const T rhs) {
  return lhs == rhs;
}

// ----------------------------------------------------------------------
// Matrix Equality Operator
//
template<typename D1, typename D2>
inline bool operator==(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return equal(~lhs, ~rhs);
}

template<typename D1, typename D2>
inline bool operator!=(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return !equal(~lhs, ~rhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_MATRIX_HPP
