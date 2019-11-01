#ifndef SYMCTRL_MATH_MATRIX_OPERATIONS_GRAM_HPP
#define SYMCTRL_MATH_MATRIX_OPERATIONS_GRAM_HPP

#include <vector>

#include <symctrl/math/matrix/dense/dense.hpp>
#include <symctrl/math/functor/kernel.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Gram Matrix
//
DenseMatrix<double> gram(KernelFunction &K,
                         const std::vector<double> &x,
                         const std::vector<double> &y);

inline DenseMatrix<double> gram(KernelFunction &K,
                                const std::vector<double> &x) {
  //
  return gram(K, x, x);
}

DenseMatrix<double> gram(KernelFunction &K,
                         const DenseMatrix<double> &X,
                         const DenseMatrix<double> &Y);

inline DenseMatrix<double> gram(KernelFunction &K,
                                const DenseMatrix<double> &X) {
  //
  return gram(K, X, X);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_OPERATIONS_GRAM_HPP
