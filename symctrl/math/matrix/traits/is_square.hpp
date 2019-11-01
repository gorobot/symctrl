#ifndef SYMCTRL_MATH_MATRIX_TRAITS_IS_SQUARE_HPP
#define SYMCTRL_MATH_MATRIX_TRAITS_IS_SQUARE_HPP

#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/static/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// is_square
//
template<typename T>
inline bool is_square(const Matrix<T> &m) {
  if((~m).nrows() != (~m).ncols()) {
    return false;
  }

  return true;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TRAITS_IS_SQUARE_HPP
