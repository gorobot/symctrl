// ---------------------------------------------------------------------------
// C Wrapper API Interface
//
// The interface provided in this file is the basis for all other language
// bindings to the library. Other language bindings should import this header
// or provide function declarations which implement the same functionality.

#ifndef SYMCTRL_C_WRAPPER_HPP
#define SYMCTRL_C_WRAPPER_HPP

#include "ctrl_export.h"

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------------
// C Wrapper for Linear Algebra Functions
//
CTRL_EXPORT void la_compute_hessenberg(CDenseMatrix *A, CDenseMatrix *result);
CTRL_EXPORT void la_compute_schur(CDenseMatrix *A,
                                  CDenseMatrix *U,
                                  CDenseMatrix *T);

CTRL_EXPORT void la_compute_eigenvalues(CDenseMatrix *A,
                                        CVecBasic *l,
                                        CDenseMatrix *v);

// ---------------------------------------------------------------------------
// C Wrapper for Analysis Functions
//
CTRL_EXPORT void ctrb(CDenseMatrix *A, CDenseMatrix *B, CDenseMatrix *result);
CTRL_EXPORT void obsv(CDenseMatrix *A, CDenseMatrix *C, CDenseMatrix *result);

// ---------------------------------------------------------------------------
// C Wrapper for StateSpace Interface
//
typedef struct StateSpace_C StateSpace_C;

CTRL_EXPORT StateSpace_C *statespace_new();
CTRL_EXPORT void statespace_free(StateSpace_C *obj);

CTRL_EXPORT void statespace_states_push_back(StateSpace_C *obj,
                                             const basic arg);
CTRL_EXPORT void statespace_states_get(StateSpace_C *obj,
                                       size_t n,
                                       basic result);
CTRL_EXPORT void statespace_states_set(StateSpace_C *obj,
                                       size_t n,
                                       const basic arg);
CTRL_EXPORT void statespace_states_erase(StateSpace_C *obj, size_t n);
CTRL_EXPORT size_t statespace_states_size(StateSpace_C *obj);

CTRL_EXPORT void statespace_inputs_push_back(StateSpace_C *obj,
                                             const basic arg);
CTRL_EXPORT void statespace_inputs_get(StateSpace_C *obj,
                                       size_t n,
                                       basic result);
CTRL_EXPORT void statespace_inputs_set(StateSpace_C *obj,
                                       size_t n,
                                       const basic arg);
CTRL_EXPORT void statespace_inputs_erase(StateSpace_C *obj, size_t n);
CTRL_EXPORT size_t statespace_inputs_size(StateSpace_C *obj);

CTRL_EXPORT void statespace_f_push_back(StateSpace_C *obj, const basic arg);
CTRL_EXPORT void statespace_f_get(StateSpace_C *obj, size_t n, basic result);
CTRL_EXPORT void statespace_f_set(StateSpace_C *obj, size_t n, const basic arg);
CTRL_EXPORT void statespace_f_erase(StateSpace_C *obj, size_t n);
CTRL_EXPORT size_t statespace_f_size(StateSpace_C *obj);

CTRL_EXPORT void statespace_g_push_back(StateSpace_C *obj, const basic arg);
CTRL_EXPORT void statespace_g_get(StateSpace_C *obj, size_t n, basic result);
CTRL_EXPORT void statespace_g_set(StateSpace_C *obj, size_t n, const basic arg);
CTRL_EXPORT void statespace_g_erase(StateSpace_C *obj, size_t n);
CTRL_EXPORT size_t statespace_g_size(StateSpace_C *obj);

CTRL_EXPORT void statespace_A_get(StateSpace_C *obj, CDenseMatrix *result);
CTRL_EXPORT void statespace_B_get(StateSpace_C *obj, CDenseMatrix *result);
CTRL_EXPORT void statespace_C_get(StateSpace_C *obj, CDenseMatrix *result);
CTRL_EXPORT void statespace_D_get(StateSpace_C *obj, CDenseMatrix *result);

CTRL_EXPORT void statespace_subs(StateSpace_C *obj,
                                 const basic k,
                                 const basic m);

CTRL_EXPORT void statespace_linearize(StateSpace_C *obj);

CTRL_EXPORT void statespace_ctrb(StateSpace_C *obj, CDenseMatrix *result);
CTRL_EXPORT int statespace_ctrb_rank(StateSpace_C *obj);

CTRL_EXPORT void statespace_obsv(StateSpace_C *obj, CDenseMatrix *result);
CTRL_EXPORT int statespace_obsv_rank(StateSpace_C *obj);

CTRL_EXPORT int statespace_is_controllable(StateSpace_C *obj);
CTRL_EXPORT int statespace_is_observable(StateSpace_C *obj);

// ---------------------------------------------------------------------------
// C Wrapper for MDP Interface
//
typedef struct MDP_C MDP_C;

CTRL_EXPORT MDP_C *mdp_new();
CTRL_EXPORT void mdp_free(MDP_C *obj);

CTRL_EXPORT size_t mdp_num_states_get(MDP_C *obj);
CTRL_EXPORT void mdp_num_states_set(MDP_C *obj, size_t n);

CTRL_EXPORT size_t mdp_num_inputs_get(MDP_C *obj);
CTRL_EXPORT void mdp_num_inputs_set(MDP_C *obj, size_t n);


CTRL_EXPORT void mdp_probabilities_set(MDP_C *obj,
                                       size_t u,
                                       size_t x,
                                       size_t xp,
                                       const double arg);
CTRL_EXPORT double mdp_probabilities_get(MDP_C *obj,
                                         size_t u,
                                         size_t x,
                                         size_t xp);
CTRL_EXPORT void mdp_probabilities_erase(MDP_C *obj, size_t n);

CTRL_EXPORT size_t mdp_probabilities_cols(MDP_C *obj);
CTRL_EXPORT size_t mdp_probabilities_rows(MDP_C *obj);

// CTRL_EXPORT void mdp_probabilities_add_matrix(MDP_C *obj, SparseMatrix_C* a);
// CTRL_EXPORT void mdp_probabilities_mul_matrix(MDP_C *obj, SparseMatrix_C* a);

CTRL_EXPORT void mdp_probabilities_add_scalar(MDP_C *obj, double a);
CTRL_EXPORT void mdp_probabilities_mul_scalar(MDP_C *obj, double a);

CTRL_EXPORT void mdp_rewards_set(MDP_C *obj,
                                 size_t u,
                                 size_t x,
                                 size_t xp,
                                 const double arg);
CTRL_EXPORT double mdp_rewards_get(MDP_C *obj,
                                   size_t u,
                                   size_t x,
                                   size_t xp);
CTRL_EXPORT void mdp_rewards_erase(MDP_C *obj, size_t n);

CTRL_EXPORT double mdp_gamma_get(MDP_C *obj);
CTRL_EXPORT void mdp_gamma_set(MDP_C *obj, const double n);

// ---------------------------------------------------------------------------
// C Wrapper for TransferFunction Interface
//
typedef struct TransferFunction_C TransferFunction_C;

CTRL_EXPORT TransferFunction_C* transferfunction_new();
CTRL_EXPORT void transferfunction_free(TransferFunction_C* obj);


#ifdef __cplusplus
}
#endif

#endif /* end of include guard: SYMCTRL_C_WRAPPER_HPP */
