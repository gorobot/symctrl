#include <vector>
#include <symengine/add.h>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>
#include <symengine/subs.h>

#include "state_space.hpp"

namespace Controls {

StateSpace::StateSpace() {}

StateSpace::~StateSpace() {}

void StateSpace::add_state(const SymEngine::RCP<const SymEngine::Basic> arg) {
  states_.push_back(arg);
}
void StateSpace::set_state(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg) {
  states_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> StateSpace::get_state(size_t n) {
  return states_.at(n);
}
size_t StateSpace::get_num_states() {
  return states_.size();
}

void StateSpace::add_input(const SymEngine::RCP<const SymEngine::Basic> arg) {
  inputs_.push_back(arg);
}
void StateSpace::set_input(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg) {
  inputs_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> StateSpace::get_input(size_t n) {
  return inputs_.at(n);
}
size_t StateSpace::get_num_inputs() {
  return inputs_.size();
}

void StateSpace::add_f(const SymEngine::RCP<const SymEngine::Basic> arg) {
  f_.push_back(arg);
}
void StateSpace::set_f(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg) {
  f_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> StateSpace::get_f(size_t n) {
  return f_.at(n);
}
size_t StateSpace::get_num_f() {
  return f_.size();
}

void StateSpace::add_g(const SymEngine::RCP<const SymEngine::Basic> arg) {
  g_.push_back(arg);
}
void StateSpace::set_g(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg) {
  g_.at(n) = arg;
}
SymEngine::RCP<const SymEngine::Basic> StateSpace::get_g(size_t n) {
  return g_.at(n);
}
size_t StateSpace::get_num_g() {
  return g_.size();
}

void StateSpace::get_A_matrix(SymEngine::DenseMatrix &result) {
  unsigned n = states_.size();
  SymEngine::DenseMatrix f;
  SymEngine::DenseMatrix x;

  result = SymEngine::DenseMatrix(n, n);

  if(n > 0 && f_.size() == n) {
    f = SymEngine::DenseMatrix(n, 1, {f_});
    x = SymEngine::DenseMatrix(n, 1, {states_});

    SymEngine::jacobian(f, x, result);
  }
}
void StateSpace::get_B_matrix(SymEngine::DenseMatrix &result) {
  unsigned n = states_.size();
  unsigned m = inputs_.size();
  SymEngine::DenseMatrix f;
  SymEngine::DenseMatrix u;

  result = SymEngine::DenseMatrix(n, m);

  if(n > 0 && f_.size() == n && m > 0) {
    f = SymEngine::DenseMatrix(n, 1, {f_});
    u = SymEngine::DenseMatrix(m, 1, {inputs_});

    SymEngine::jacobian(f, u, result);
  }
}
void StateSpace::get_C_matrix(SymEngine::DenseMatrix &result) {
  unsigned n = states_.size();
  unsigned p = g_.size();
  SymEngine::DenseMatrix g;
  SymEngine::DenseMatrix x;

  result = SymEngine::DenseMatrix(p, n);

  if(n > 0 && p > 0) {
    g = SymEngine::DenseMatrix(p, 1, {g_});
    x = SymEngine::DenseMatrix(n, 1, {states_});

    SymEngine::jacobian(g, x, result);
  }
}
void StateSpace::get_D_matrix(SymEngine::DenseMatrix &result) {
  unsigned m = inputs_.size();
  unsigned p = g_.size();
  SymEngine::DenseMatrix g;
  SymEngine::DenseMatrix u;

  result = SymEngine::DenseMatrix(p, m);

  if(m > 0 && p > 0) {
    g = SymEngine::DenseMatrix(p, 1, {g_});
    u = SymEngine::DenseMatrix(m, 1, {inputs_});

    SymEngine::jacobian(g, u, result);
  }
}

bool check_abcd(SymEngine::MatrixBase &A,
                SymEngine::MatrixBase &B,
                SymEngine::MatrixBase &C,
                SymEngine::MatrixBase &D) {
  //
  size_t n = A.ncols();
  size_t m = B.ncols();
  size_t p = C.nrows();

  // A = [n, n]
  // B = [n, m]
  // C = [p, n]
  // D = [p, m]
}

void set_abcd(StateSpace &obj,
              SymEngine::DenseMatrix &A,
              SymEngine::DenseMatrix &B,
              SymEngine::DenseMatrix &C,
              SymEngine::DenseMatrix &D) {
  //
  size_t n = obj.get_num_states();
  size_t m = obj.get_num_inputs();
  size_t p = obj.get_num_g();
  size_t i, j;

  SymEngine::DenseMatrix x, u, M, R;
  SymEngine::vec_basic fv, gv, xv, xu;

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

// ----------------------------------------------------------------------
// Linearization
//
void linearize(StateSpace &obj) {
  size_t n = obj.get_num_states();
  size_t m = obj.get_num_inputs();
  size_t p = obj.get_num_g();

  // Substitute x and u for 0 in A, B, C, D.
  SymEngine::map_basic_basic d;
  SymEngine::DenseMatrix A, B, C, D;

  size_t i, j;
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

  set_abcd(obj, A, B, C, D);
}

} // Controls
