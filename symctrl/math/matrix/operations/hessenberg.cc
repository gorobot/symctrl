#include <symengine/add.h>
#include <symengine/pow.h>
#include <symengine/visitor.h>

#include "linalg.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Hessenberg
//
void hessenberg(SymEngine::DenseMatrix &A,
                SymEngine::DenseMatrix &result) {
  //
  unsigned row = A.nrows();
  unsigned col = A.ncols();

  // TODO: Perform squareness checking.
  if(!is_square(A)) {
    // error
  }

  SymEngine::RCP<const SymEngine::Basic> t;
  SymEngine::vec_basic Av = A.as_vec_basic();
  SymEngine::vec_basic reflector;
  SymEngine::vec_basic tmp, uu;

  SymEngine::DenseMatrix M, R;

  int i, j, k, c, idx, len;

  for(k = 0; k < row - 2; k++) {
    // Compute Householder reflector.
    len = col - (k + 1);
    reflector = SymEngine::vec_basic(len);

    idx = 0;
    for(i = k + 1; i < row; i++) {
      reflector[idx++] = Av[i*col + k];
    }

    householder_reflector(reflector);

    // Form u*u'
    uu = SymEngine::vec_basic(len*len);
    for(i = 0; i < len; i++) { // row
      for(j = 0; j < len; j++) { // col
        uu[i*len + j] = SymEngine::mul(reflector[i], reflector[j]);
      }
    }

    // Assign u*u' to M.
    M = SymEngine::DenseMatrix(len, len, {uu});

    // Get the submatrix from A.
    tmp = SymEngine::vec_basic((row - (k + 1))*(col - k));
    submatrix_from_vec(Av, k + 1, row, k, col, tmp);

    // Assign the submatrix of A to R.
    R = SymEngine::DenseMatrix(row - (k + 1), col - k, {tmp});

    // A_r = A_r - 2*u*u'*A_r
    householder_transform_l(R, M);

    // Substitute the new values back into A.
    tmp = R.as_vec_basic();
    vec_to_submatrix(tmp, k + 1, row, k, col, Av);

    // Assign u*u' to M.
    M = SymEngine::DenseMatrix(len, len, {uu});

    // Get the submatrix from A.
    tmp = SymEngine::vec_basic(row*(col - (k + 1)));
    submatrix_from_vec(Av, 0, row, k + 1, col, tmp);

    // Assign the submatrix of A to R.
    R = SymEngine::DenseMatrix(row, col - (k + 1), {tmp});

    // A_c = A_c - 2*A_c*u*u'
    householder_transform_r(R, M);

    // Substitute the new values back into A.
    tmp = R.as_vec_basic();
    vec_to_submatrix(tmp, 0, row, k + 1, col, Av);

    // Set remainders of operations to zero. This is the approximation.
    // for(i = k + 2; i < row; i++) {
    //   Av[i*col + k] = SymEngine::zero;
    // }
  }

  result = SymEngine::DenseMatrix(row, col, {Av});
}

} // Controls
