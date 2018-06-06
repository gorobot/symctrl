#ifndef MODELS_UTILS_EIG_HPP
#define MODELS_UTILS_EIG_HPP

namespace Controls {

void compute_eigenvalues(SymEngine::DenseMatrix &A,
                         SymEngine::vec_basic &l,
                         SymEngine::DenseMatrix &v);

void compute_hessenberg(SymEngine::DenseMatrix &A,
                        SymEngine::DenseMatrix &result);

void compute_schur(SymEngine::DenseMatrix &A,
                   SymEngine::DenseMatrix &U,
                   SymEngine::DenseMatrix &T,
                   size_t n_iter = 10);

} // Controls

#endif /* end of include guard: MODELS_UTILS_EIG_HPP */
