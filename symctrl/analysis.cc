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

// ----------------------------------------------------------------------
// Linearization
//
void linearize(StateSpace &obj) {
  size_t n = obj.get_num_states();
  size_t m = obj.get_num_inputs();
  size_t p = obj.get_num_g();

  // Substitute x and u for 0 in A, B, C, D.
  SymEngine::map_basic_basic d;
  SymEngine::DenseMatrix A, B, C, D, x, u, M, R;
  SymEngine::vec_basic fv, gv, xv, xu;

  int i = 0;
  int j = 0;
  for(i = 0; i < n; i++) {
    d[obj.get_state(i)] = SymEngine::integer(0);
  }

  for(i = 0; i < m; i++) {
    d[obj.get_input(i)] = SymEngine::integer(0);
  }

  obj.get_A_matrix(A);
  obj.get_B_matrix(B);
  obj.get_C_matrix(C);
  obj.get_D_matrix(D);

  for(i = 0; i < A.nrows(); i++) { // rows
    for(j = 0; j < A.ncols(); j++) { // cols
      A.set(i, j, SymEngine::ssubs(A.get(i, j), d));
    }
  }
  for(i = 0; i < B.nrows(); i++) { // rows
    for(j = 0; j < B.ncols(); j++) { // cols
      B.set(i, j, SymEngine::ssubs(B.get(i, j), d));
    }
  }
  for(i = 0; i < C.nrows(); i++) { // rows
    for(j = 0; j < C.ncols(); j++) { // cols
      C.set(i, j, SymEngine::ssubs(C.get(i, j), d));
    }
  }
  for(i = 0; i < D.nrows(); i++) { // rows
    for(j = 0; j < D.ncols(); j++) { // cols
      D.set(i, j, SymEngine::ssubs(D.get(i, j), d));
    }
  }

  for(i = 0; i < n; i++) {
    xv.push_back(obj.get_state(i));
    // x.set(i, 1, obj.get_state(i));
  }
  x = SymEngine::DenseMatrix(n, 1, {xv});

  for(i = 0; i < m; i++) {
    xu.push_back(obj.get_input(i));
    // u.set(i, 1, obj.get_input(i));
  }
  u = SymEngine::DenseMatrix(m, 1, {xu});

  // f = A*x + B*u
  M = SymEngine::DenseMatrix(n, 1);
  R = SymEngine::DenseMatrix(n, 1);
  A.mul_matrix(x, M);
  B.mul_matrix(u, R);
  M.add_matrix(R, M);
  fv = M.as_vec_basic();
  for(i = 0; i < fv.size(); i++) {
    obj.set_f(i, fv[i]);
  }

  // g = C*x + D*u
  M = SymEngine::DenseMatrix(p, 1);
  R = SymEngine::DenseMatrix(p, 1);
  C.mul_matrix(x, M);
  D.mul_matrix(u, R);
  M.add_matrix(R, M);
  gv = M.as_vec_basic();
  for(i = 0; i < gv.size(); i++) {
    obj.set_g(i, gv[i]);
  }
}

// void linearize(SymEngine::vec_basic &eq) {
// //   // TODO: Size checking. Number of equilibrium points must equal number of states & inputs.
// //
// //
// //   // int i = 0;
// //   // for(i = 0; i < states_.size(); i++) {
// //   //   f_[i] = SymEngine::ssubs(states_[i], eq[i]);
// //   // }
// //   //
// //   // for(i = states_.size(); i < eq.size(); i++) {
// //   //   f_[i] = SymEngine::ssubs()
// //   // }
// }


} // Controls
