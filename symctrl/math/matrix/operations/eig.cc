#include <symengine/add.h>
#include <symengine/pow.h>
#include <symengine/real_double.h>

#include "eig.hpp"
#include "linalg.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Eigenvalues
//
void eigenvalues(SymEngine::DenseMatrix &A,
                 SymEngine::vec_basic &l,
                 SymEngine::DenseMatrix &V) {
  // TODO: Perform squareness checking.
  size_t i;
  size_t n = A.ncols();

  V = SymEngine::DenseMatrix(n, n);

  if(!is_numeric(A)) {
    // Compute using polynomial roots.
    auto solns = SymEngine::eigen_values(A);

    for(auto e = solns->get_args().begin(); e != solns->get_args().end(); ++e) {
      l.push_back(*e);
    }
    // for(i = 0; i < solns.size(); i++) {
    //   l.push_back(solns[i]);
    // }

    V = SymEngine::DenseMatrix(n, n);
    SymEngine::eye(V);

  }
  else {
    // Compute the Schur decomposition.
    SymEngine::DenseMatrix T;
    T = SymEngine::DenseMatrix(n, n);

    schur(A, V, T);

    for(i = 0; i < n; i++) {
      l.push_back(T.get(i, i));
    }
  }
}

// Iterative power method.
SymEngine::RCP<const SymEngine::Basic>
get_first_eigenvalue(SymEngine::DenseMatrix &A, double tol) {
  //
  size_t row, col, i, j;
  row = A.nrows();
  col = A.ncols();

  SymEngine::DenseMatrix z, q, R, M;
  SymEngine::vec_basic t;
  SymEngine::RCP<const SymEngine::Basic> a, ldiff, lambda;
  SymEngine::RCP<const SymEngine::Basic> seTol = SymEngine::number(tol);

  // seTol = SymEngine::Number(tol);

  R = SymEngine::DenseMatrix(1, 1);
  M = SymEngine::DenseMatrix(1, row);

  z = SymEngine::DenseMatrix(row, 1);
  q = SymEngine::DenseMatrix(row, 1);
  SymEngine::zeros(q);
  q.set(0, 0, SymEngine::one);

  lambda = SymEngine::zero;

  size_t k = 0;

  do {
    SymEngine::zeros(z);

    // z^(k) = A*q^(k-1)

    // A.mul_matrix(q, z);
    for(i = 0; i < row; i++) {
      for(j = 0; j < col; j++) {
        a = SymEngine::mul(q.get(j, 0), A.get(i, j));
        z.set(i, 0, SymEngine::add(z.get(i, 0), a));
      }
    }

    // q^(k) = z^(k)/|z^(k)|

    t = z.as_vec_basic();
    z.mul_scalar(SymEngine::pow(norm2(t), SymEngine::minus_one), q);

    // lambda^(k) = [q^(k)]^H*A*q^(k)

    // A.mul_matrix(q, z);
    for(i = 0; i < row; i++) {
      for(j = 0; j < col; j++) {
        a = SymEngine::mul(q.get(j, 0), A.get(i, j));
        z.set(i, 0, SymEngine::add(z.get(i, 0), a));
      }
    }

    conjugate_transpose(q, M);

    M.mul_matrix(z, R);

    t = R.as_vec_basic();
    // ldiff = SymEngine::abs(SymEngine::sub(lambda, t[0]));
    lambda = t[0];

    k++;
  } while( k < 200 );
  // } while( seTol->compare(*ldiff) != 1 );

  return lambda;
}

} // Controls
