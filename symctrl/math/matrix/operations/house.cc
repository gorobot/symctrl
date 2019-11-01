#include <symengine/add.h>
#include <symengine/pow.h>
#include <symengine/visitor.h>

#include "linalg.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Compute Householder Reflector
//
void householder_reflector(SymEngine::vec_basic &u) {
  SymEngine::RCP<const SymEngine::Basic> t;

  // Compute the norm.
  t = norm2(u);

  // u[1] = u[1] + sign(u[1]) * |u|
  u[0] = SymEngine::add(u[0], SymEngine::mul(SymEngine::sign(u[0]), t));

  // u = u/|u|
  normalize(u);
}

// ----------------------------------------------------------------------
// Apply Householder Reflector
//
// Apply the householder reflector from the left.
// A_r = A_r - 2*u*u'*A_r
void householder_transform_l(SymEngine::DenseMatrix &A,
                             SymEngine::vec_basic &u) {
  // // Form u*u'
  SymEngine::DenseMatrix M;
  mul_vec(u, M);

  householder_transform_l(A, M);
}

void householder_transform_l(SymEngine::DenseMatrix &A,
                             SymEngine::DenseMatrix &M) {
  // Perform matrix operations.
  M.mul_matrix(A, M);
  M.mul_scalar(SymEngine::integer(-2), M);
  A.add_matrix(M, A);
}

// Apply the householder reflector from the right.
// A_c = A_c - 2*A_c*u*u'
void householder_transform_r(SymEngine::DenseMatrix &A,
                             SymEngine::vec_basic &u) {
  //
  SymEngine::DenseMatrix M;
  mul_vec(u, M);

  householder_transform_r(A, M);
}

void householder_transform_r(SymEngine::DenseMatrix &A,
                             SymEngine::DenseMatrix &M) {
  // Perform matrix operations.
  A.mul_matrix(M, M);
  M.mul_scalar(SymEngine::integer(-2), M);
  A.add_matrix(M, A);
}

} // Controls
