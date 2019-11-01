#include <cmath>
#include <numeric>
#include <vector>

#include "kernel.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Kernel coefficient vector function.
//
template<typename T>
void kernel_coefficient_vector(const Controls::DenseMatrix<double> &K,
                               const double lambda,
                               std::vector<double> &alpha) {
  //
  size_t n_ = K.nrows();

  // Calculate K + (lambda * n_ * I)
  for(size_t i = 0; i < n_; i++) {
    // K(i, i) += lambda * n_;
  }

  // Calculate W = (K + (lambda * n_ * I))^-1
  Controls::DenseMatrix<double> W(n_, n_);

}

// ----------------------------------------------------------------------
// Kernel estimate function.
//
template<typename T>
void kernel_estimate(const std::vector<T> &x,
                     const std::vector<T> &y,
                     const std::vector<double> &alpha,
                     KernelFunction<T> *K,
                     std::vector<double> &result) {
  //
  double sum_;

  Controls::DenseMatrix<double> M(x.size(), y.size());
  K->gramian(x, y, M);

  // Perform the matrix multiplication (M * alpha).
#pragma omp parallel for
  for(size_t i = 0; i < M.nrows(); i++) {
    sum_ = 0;

    for(size_t j = 0; j < M.ncols(); j++) {
      sum_ += M(i, j) * alpha.at(j);
    }

    result.at(i) = sum_;
  }
}

// // ----------------------------------------------------------------------
// // Gramian
// //
// void gramian(KernelFunction &K,
//              const std::vector<double> &x,
//              const std::vector<double> &y,
//              Controls::DenseMatrix<double> &result) {
//   //
//   size_t i, j;
//   // std::vector<double> x_(1);
//   // std::vector<double> y_(1);
//
// #pragma omp parallel for
//   for(i = 0; i < x.size(); i++) {
//     for(j = 0; j < y.size(); j++) {
//       K.eval({x[i]}, {y[j]}, result(i, j));
//     }
//   }
// }
//
// void gramian(KernelFunction &K,
//              const std::vector<double> &x,
//              Controls::DenseMatrix<double> &result) {
//   //
//   gramian(K, x, x, result);
// }
//
// void gramian(KernelFunction &K,
//              const Controls::DenseMatrix<double> &X,
//              const Controls::DenseMatrix<double> &Y,
//              Controls::DenseMatrix<double> &result) {
//   //
//   size_t i, j, k;
//   std::vector<double> x_(X.ncols());
//   std::vector<double> y_(Y.ncols());
//
//   // Iterate over every row in X.
//   for(i = 0; i < X.nrows(); i++) {
//     // Extract the ith row from X.
//     for(k = 0; k < X.ncols(); k++) {
//       x_[k] = X(i, k);
//     }
//
//     for(j = 0; j < Y.nrows(); j++) {
//       // Extract the jth row from X.
//       for(k = 0; k < Y.ncols(); k++) {
//         y_[k] = Y(j, k);
//       }
//
//       K.eval(x_, y_, result(i, j));
//     }
//   }
// }
//
// void gramian(KernelFunction &K,
//              const Controls::DenseMatrix<double> &X,
//              Controls::DenseMatrix<double> &result) {
//   //
//   gramian(K, X, X, result);
// }

} // Controls
