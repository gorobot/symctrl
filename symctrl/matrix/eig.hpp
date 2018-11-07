#ifndef MODELS_UTILS_EIG_HPP
#define MODELS_UTILS_EIG_HPP

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

namespace Controls {

// Should this use the Schur decomposition, or the polynomial solve method?
void eigenvalues(SymEngine::DenseMatrix &A,
                 SymEngine::vec_basic &l,
                 SymEngine::DenseMatrix &v);

SymEngine::RCP<const SymEngine::Basic>
get_first_eigenvalue(SymEngine::DenseMatrix &A, double tol);

// Use eigenvalues or the Schur decomposition to compute eigenvectors.
void eigenvectors();

// Compute the jordan form using eigenvector matrix.
void jordan_form();

} // Controls

#endif /* end of include guard: MODELS_UTILS_EIG_HPP */
