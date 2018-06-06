#include <symengine/add.h>
#include <symengine/pow.h>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>
#include <symengine/visitor.h>

#include "eig.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Eigenvalues
//
void compute_eigenvalues(SymEngine::DenseMatrix &A,
                         SymEngine::vec_basic &l,
                         SymEngine::DenseMatrix &v) {
  // TODO: Perform squareness checking.
  size_t n = A.ncols();

  SymEngine::DenseMatrix U, T;

  U = SymEngine::DenseMatrix(n, n);
  T = SymEngine::DenseMatrix(n, n);

  // Compute the Schur decomposition.
  compute_schur(A, v, T);

  int i = 0;
  for(i = 0; i < n; i++) {
    l.push_back(T.get(i, i));
  }
}

// ----------------------------------------------------------------------
// 2-Norm
//
SymEngine::RCP<const SymEngine::Basic> norm2(SymEngine::vec_basic &v) {
  SymEngine::RCP<const SymEngine::Basic> t = SymEngine::zero;
  int i = 0;
  for(i = 0; i < v.size(); i++) {
    // printf("%s\n", v[i]->__str__().c_str());
    t = SymEngine::add(t, SymEngine::pow(v[i], SymEngine::integer(2)));
  }
  t = SymEngine::pow(t, SymEngine::div(SymEngine::one, SymEngine::integer(2)));

  return t;
}

// ----------------------------------------------------------------------
// Vector Normalization
//
// v = v/|v|
void normalize(SymEngine::vec_basic &v) {
  SymEngine::RCP<const SymEngine::Basic> t = norm2(v);
  int i = 0;
  for(i = 0; i < v.size(); i++) {
    v[i] = SymEngine::div(v[i], t);
  }
}

// ----------------------------------------------------------------------
// Hessenberg
//
void compute_hessenberg(SymEngine::DenseMatrix &A,
                        SymEngine::DenseMatrix &result) {
  //
  unsigned row = A.nrows();
  unsigned col = A.ncols();

  // TODO: Perform squareness checking.
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

    // Compute the norm.
    t = norm2(reflector);

    // u[1] = u[1] + sign(u[1]) * |u|
    reflector[0] = SymEngine::add(reflector[0],
                                  SymEngine::mul(SymEngine::sign(reflector[0]),
                                                 t));

    // u = u/|u|
    normalize(reflector);

    // Form u*u'
    uu = SymEngine::vec_basic(len*len);
    for(i = 0; i < len; i++) { // row
      for(j = 0; j < len; j++) { // col
        uu[i*len + j] = SymEngine::mul(reflector[i], reflector[j]);
      }
    }

    // A_b = A_b - 2*u*u'*A_b
    M = SymEngine::DenseMatrix(len, len, {uu});

    // Get the submatrix from A.
    tmp = SymEngine::vec_basic((row - (k + 1))*(col - k));
    idx = 0;
    for(i = k + 1; i < row; i++) { // row
      for(j = k; j < col; j++) { //col
        tmp[idx++] = Av[i*col + j];
      }
    }

    // Assign the submatrix of A to R.
    R = SymEngine::DenseMatrix(row - (k + 1), col - k, {tmp});
    // Perform matrix operations.
    M.mul_matrix(R, M);
    M.mul_scalar(SymEngine::integer(-2), M);
    R.add_matrix(M, R);
    tmp = R.as_vec_basic();

    // Substitute the new values back into A.
    idx = 0;
    for(i = k + 1; i < row; i++) { // row
      for(j = k; j < col; j++) { //col
        Av[i*col + j] = tmp[idx++];
      }
    }

    // A_c = A_c - 2*A_c*u*u'
    M = SymEngine::DenseMatrix(len, len, {uu});

    // Get the submatrix from A.
    tmp = SymEngine::vec_basic(row*(col - (k + 1)));
    idx = 0;
    for(i = 0; i < row; i++) { // row
      for(j = k + 1; j < col; j++) { //col
        tmp[idx++] = Av[i*col + j];
      }
    }

    // Assign the submatrix of A to R.
    R = SymEngine::DenseMatrix(row, col - (k + 1), {tmp});
    // Perform matrix operations.
    R.mul_matrix(M, M);
    M.mul_scalar(SymEngine::integer(-2), M);
    R.add_matrix(M, R);
    tmp = R.as_vec_basic();

    // Substitute the new values back into A.
    idx = 0;
    for(i = 0; i < row; i++) { // row
      for(j = k + 1; j < col; j++) { //col
        Av[i*col + j] = tmp[idx++];
      }
    }

    // Set remainders of operations to zero. This is the approximation.
    for(i = k + 2; i < row; i++) {
      Av[i*col + k] = SymEngine::zero;
    }
  }

  result = SymEngine::DenseMatrix(row, col, {Av});
}

// ----------------------------------------------------------------------
// Schur
//
void compute_schur(SymEngine::DenseMatrix &A,
                   SymEngine::DenseMatrix &U,
                   SymEngine::DenseMatrix &T,
                   size_t n_iter) {
  // TODO: Perform squareness checking.
  unsigned row = A.nrows();
  unsigned col = A.ncols();

  SymEngine::DenseMatrix Q, R, W, V;
  Q = SymEngine::DenseMatrix(row, col);
  R = SymEngine::DenseMatrix(row, col);

  W = SymEngine::DenseMatrix(A);
  V = SymEngine::DenseMatrix(row, col);
  SymEngine::eye(V);

  int i = 0;
  for(i = 0; i < n_iter; i++) {
    QR(W, Q, R);
    R.mul_matrix(Q, W);
    V.mul_matrix(Q, V);
  }

  U = V;
  T = W;
}

} // Controls
