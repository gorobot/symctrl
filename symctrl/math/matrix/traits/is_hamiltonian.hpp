#ifndef SYMCTRL_MATH_MATRIX_TRAITS_IS_HAMILTONIAN_HPP
#define SYMCTRL_MATH_MATRIX_TRAITS_IS_HAMILTONIAN_HPP

#include <symctrl/math/matrix/block.hpp>
#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/constant.hpp>
#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// is_hamiltonian
//
template<typename DT>
inline bool is_hamiltonian(const Matrix<DT> &m) {
  if((~m).nrows() != (~m).ncols()) {
    return false;
  }

  // Even number of rows. (2n x 2n matrices only)
  if((~m).nrows() % 2 != 0) {
    return false;
  }

  size_t n_ = (~m).nrows();

  DenseMatrix<typename DT::type> I(n_, n_);
  DenseMatrix<typename DT::type> zero(n_, n_);

  I = 0;
  zero = 0;

  for(size_t i = 0; i < n_; i++) {
    I(i, i) = 1;
  }

  BlockMatrix<typename DT::type> J_block(2, 2, {zero, I, -I, zero});
  DenseMatrix<typename DT::type> J = J_block.as_dense();

  DenseMatrix<typename DT::type> A(n_, n_);
  DenseMatrix<typename DT::type> B(n_, n_);
  A = transpose(J*m);
  B = J*m;

  for(size_t i = 0; i < A.size(); i++) {
    std::cout << A[i] << " ?= " << B[i] << '\n';
  }

  if(transpose(J*m) != J*m) {
    return false;
  }

  return true;
}

// template<typename T>
// inline bool is_hamiltonian(const BlockMatrix<T> &m) {
//   if((~m).nrows() != 2 || (~m).ncols() != 2) {
//     return false;
//   }
//
//   const size_t n_ = (~m)[0].nrows();
//   const size_t m_ = (~m)[0].ncols();
//
//   if(n_ != m_) {
//     return false;
//   }
//
//   // Even number of rows. (2n x 2n matrices only)
//   if(n_ % 2 != 0) {
//     return false;
//   }
//
//   for(size_t i = 1; i < (~m).size(); i++) {
//     if((~m)[i].nrows() != n_ || (~m)[i].ncols() != m_) {
//       return false;
//     }
//   }
//
//   DenseMatrix<T> I(n_, m_);
//   DenseMatrix<T> zero(n_, m_);
//
//   I = 0;
//   zero = 0;
//
//   for(size_t i = 0; i < n_; i++) {
//     I(i, i) = 1;
//   }
//
//   BlockMatrix<T> J(2, 2, {zero, I, -I, zero});
//
//   if(transpose(J*m) != J*m) {
//     return false;
//   }
//
//   BlockMatrix<T> A(2, 2);
//   BlockMatrix<T> B(2, 2);
//   A = transpose(J*m);
//   B = J*m;
//   DenseMatrix<T> ADense = A.as_dense();
//   DenseMatrix<T> BDense = B.as_dense();
//
//   for(size_t i = 0; i < ADense.size(); i++) {
//     std::cout << ADense[i] << " ?= " << BDense[i] << '\n';
//   }
//
//   return true;
//
// }

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TRAITS_IS_HAMILTONIAN_HPP
