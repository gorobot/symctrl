#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/subs.h>

#include "analysis.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Controllability
//
void ctrb(StateSpace &obj, SymEngine::DenseMatrix &result) {
  SymEngine::DenseMatrix A;
  SymEngine::DenseMatrix B;
  obj.get_A_matrix(A);
  obj.get_B_matrix(B);

  ctrb(A, B, result);
}
void ctrb(SymEngine::DenseMatrix &A,
          SymEngine::DenseMatrix &B,
          SymEngine::DenseMatrix &result) {

  // TODO: Add dimension checking.
  unsigned n = A.ncols();
  unsigned m = B.ncols();
  SymEngine::DenseMatrix M;

  result = SymEngine::DenseMatrix(B);
  M = SymEngine::DenseMatrix(result);

  int k = 0;
  for(k = m; k < n*m; k += m) {
    // Keep a running matrix.
    A.mul_matrix(M, M);
    result.row_join(M);
  }
}

int ctrb_rank(StateSpace &obj) {
  SymEngine::DenseMatrix co;
  ctrb(obj, co);
  //
  // SymEngine::permutelist pl;
  // SymEngine::pivoted_gaussian_elimination(co, result, pl);
  return co.rank();
}

// ----------------------------------------------------------------------
// Observability
//
void obsv(StateSpace &obj, SymEngine::DenseMatrix &result) {
  SymEngine::DenseMatrix A;
  SymEngine::DenseMatrix C;
  obj.get_A_matrix(A);
  obj.get_C_matrix(C);

  obsv(A, C, result);
}
void obsv(SymEngine::DenseMatrix &A,
          SymEngine::DenseMatrix &C,
          SymEngine::DenseMatrix &result) {

  // TODO: Add dimension checking.
  unsigned n = A.nrows();
  unsigned p = C.nrows();
  SymEngine::DenseMatrix M;

  result = SymEngine::DenseMatrix(C);
  M = SymEngine::DenseMatrix(result);

  int k = 0;
  for(k = p; k < n*p; k += p) {
    // Keep a running matrix.
    M.mul_matrix(A, M);
    result.col_join(M);
  }
}

} // Controls
