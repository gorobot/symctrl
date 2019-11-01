#ifndef SYMCTRL_KERNEL_HPP
#define SYMCTRL_KERNEL_HPP

#include <vector>

#include "matrix/dense.hpp"
#include "function.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Calculate Kernel Coefficient Vector
//
// Inputs:
// K: Kernel Matrix (Gramian) of samples {(x_i, a_i), ..., (x_m, a_m)}
// lambda: regularization parameter
// void kernel_coeff(DenseMatrix<double> &K);

// ----------------------------------------------------------------------
// Calculate Conditional Estimate
//
// Inputs:
// L: Kernel function on S

// ----------------------------------------------------------------------
//
//


// template<typename T>
// void kernel_estimate(const Controls::DenseMatrix<T> &X,
//                      const Controls::DenseMatrix<T> &Y,
//                      const std::vector<double> &alpha,
//                      KernelFunction<T> *K,
//                      std::vector<double> &result) {
//   //
//   double sum_;
//
//   Controls::DenseMatrix<double> M(X.nrows(), Y.nrows());
//   K->gramian(X, Y, M);
//
//   // Perform the matrix multiplication (M * alpha).
// #pragma omp parallel for
//   for(size_t i = 0; i < M.nrows(); i++) {
//     sum_ = 0;
//
//     for(size_t j = 0; j < M.ncols(); j++) {
//       sum_ += M(i, j) * alpha.at(j);
//     }
//
//     result.at(i) = sum_;
//   }
// }
//
// template<typename T>
// void kernel_estimate(const Controls::DenseMatrix<T> &X,
//                      std::vector<double> &alpha,
//                      KernelFunction<T> *K,
//                      std::vector<double> &result) {
//   //
//   size_t i, j;
//   T sum_;
//
//   Controls::DenseMatrix<T> M(X.nrows(), X.nrows());
//   K->gramian(X, M);
//
//   // Perform the matrix multiplication (M * alpha).
//   for(i = 0; i < M.nrows(); i++) {
//     sum_ = 0;
//
//     for(j = 0; j < M.ncols(); j++) {
//       sum_ += M(i, j) * alpha.at(j);
//     }
//
//     result.at(i) = sum_;
//   }
// }

} // Controls

#endif // SYMCTRL_KERNEL_HPP
