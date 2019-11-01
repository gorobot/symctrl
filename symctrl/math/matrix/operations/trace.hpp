#ifndef SYMCTRL_MATH_MATRIX_OPERATIONS_TRACE_HPP
#define SYMCTRL_MATH_MATRIX_OPERATIONS_TRACE_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// trace
//
template<typename DT>
inline typename DT::type trace(const Matrix<DT> &m) {
  SYMCTRL_ASSERT((~m).nrows() == (~m).ncols());

  typename DT::type result = 0;
  size_t m_ = (~m).ncols();

  for(size_t i = 0; i < m_; i++) {
    result += (~m)[i*m_ + i];
  }

  return result;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_OPERATIONS_TRACE_HPP
