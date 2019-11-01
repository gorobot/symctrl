#ifndef SYMCTRL_MATH_MATRIX_TRAITS_IS_SYMMETRIC_HPP
#define SYMCTRL_MATH_MATRIX_TRAITS_IS_SYMMETRIC_HPP

#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/expression/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// is_symmetric
//
template<typename DT>
inline bool is_symmetric(const Matrix<DT> &m) {
  if((~m).nrows() != (~m).ncols()) {
    return false;
  }

  for(size_t i = 1; i < (~m).nrows(); ++i) {
    for(size_t j = 0; j < i; ++j) {
      if(!equal((~m)(i, j), (~m)(j, i))) {
        return false;
      }
    }
  }

  return true;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TRAITS_IS_SYMMETRIC_HPP
