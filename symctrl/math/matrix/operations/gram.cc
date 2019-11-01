#include <symctrl/math/matrix/operations/gram.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Gram Matrix
//
DenseMatrix<double> gram(KernelFunction &K,
                         const std::vector<double> &x,
                         const std::vector<double> &y) {
  //
  SYMCTRL_ASSERT(x.size() == y.size());
  size_t n_ = x.size();

  size_t i, j;
  std::vector<double> v_(n_);

#pragma omp parallel for
  for(i = 0; i < x.size(); i++) {
    for(j = 0; j < y.size(); j++) {
      v_[i*n_ + j] = K.eval({x[i]}, {y[j]});
    }
  }

  return DenseMatrix<double>(n_, n_, v_);
}

DenseMatrix<double> gram(KernelFunction &K,
                         const DenseMatrix<double> &X,
                         const DenseMatrix<double> &Y) {
  //
  SYMCTRL_ASSERT(X.nrows() == Y.nrows());
  size_t n_ = X.nrows();
  size_t m_ = X.ncols();

  std::vector<double> x_(X.ncols());
  std::vector<double> y_(Y.ncols());
  std::vector<double> v_(n_*n_);

  // Iterate over every row in X.
  for(size_t i = 0; i < n_; i++) {
    // Extract the ith row from X.
    x_ = X.row(i).as_vec();

    for(size_t j = 0; j < n_; j++) {
      // Extract the jth row from Y.
      y_ = Y.row(j).as_vec();

      v_[i*n_ + j] = K.eval(x_, y_);
    }
  }

  return DenseMatrix<double>(n_, n_, v_);
}

} // Math
} // Controls
