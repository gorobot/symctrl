#include <symengine/add.h>
#include <symengine/pow.h>

#include "linalg.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Schur
//
void schur(SymEngine::DenseMatrix &A,
           SymEngine::DenseMatrix &U,
           SymEngine::DenseMatrix &T,
           size_t n_iter) {
  size_t i;
  unsigned row = A.nrows();
  unsigned col = A.ncols();

  // TODO: Perform squareness checking.
  if(!is_square(A)) {
    // error
  }

  // TODO: Perform numerical checking.
  if(!is_numeric(A)) {
    // error
  }

  SymEngine::DenseMatrix H, Q, R, W, V;
  H = SymEngine::DenseMatrix(A);
  Q = SymEngine::DenseMatrix(row, col);
  R = SymEngine::DenseMatrix(row, col);

  // Compute the upper-Hessenberg form of A.
  // hessenberg(A, H);

  W = SymEngine::DenseMatrix(H);
  V = SymEngine::DenseMatrix(row, col);
  SymEngine::eye(V);

  for(i = 0; i < 200; i++) {
    QR(W, Q, R);
    R.mul_matrix(Q, W);
    V.mul_matrix(Q, V);

    // TODO: Convert to tolerance checking.
    // Absolute difference is less than some parameter.
  }

  U = SymEngine::DenseMatrix(V);
  T = SymEngine::DenseMatrix(W);

}


} // Controls
