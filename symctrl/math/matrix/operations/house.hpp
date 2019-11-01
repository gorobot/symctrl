#ifndef SYMCTRL_MATH_MATRIX_OPERATIONS_HOUSE_HPP
#define SYMCTRL_MATH_MATRIX_OPERATIONS_HOUSE_HPP

#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/vector.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// HouseHolder Reflector
//
// M = I - 2*v*v^T
template<typename T>
inline DenseMatrix<T> householder_reflector(const Vector<T> &m) {
  return -2 * v * transpose(v);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_OPERATIONS_HOUSE_HPP
