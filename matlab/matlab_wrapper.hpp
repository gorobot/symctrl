// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//

// API Rules
// - Only use C standard types that convert to Matlab basic types. Convert to
//   more advanced types in Matlab or C++.
// - Do not return pointers. Modify pointers in the parameters. Only return
//   simple types if the values are scalar. This is because Matlab
//   automatically adds a return variable to interpreted function calls to a
//   shared library if the parameter is changed.
// - Implement Matlab array-handling only. Do not re-invent functionality or
//   create new functionality, unless it is unique and specific to Matlab.

#ifndef CONTROL_MATLAB_MATLAB_WRAPPER_HPP
#define CONTROL_MATLAB_MATLAB_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------
// Linear algebra wrapper functions.
//
void ml_linalg_hessenberg(int len, char **A, char **result);
void ml_linalg_schur(int len, char **A, char **U, char **T);

void ml_linalg_eigenvalues(int len, char **A, char **l, char **v);

void ml_linalg_first_eigenvalue(int len, char **A, char **l, double tol);

// ----------------------------------------------------------------------
// State Space wrapper functions.
//
typedef struct StateSpace_C StateSpace_C;

StateSpace_C* ml_statespace_new();

void ml_statespace_free(StateSpace_C *obj);

void ml_statespace_states_get(StateSpace_C *obj, char **result);
void ml_statespace_states_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_states_size(StateSpace_C *obj);

void ml_statespace_inputs_get(StateSpace_C *obj, char **result);
void ml_statespace_inputs_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_inputs_size(StateSpace_C *obj);

void ml_statespace_f_get(StateSpace_C *obj, char **result);
void ml_statespace_f_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_f_size(StateSpace_C *obj);

void ml_statespace_g_get(StateSpace_C *obj, char **result);
void ml_statespace_g_set(StateSpace_C *obj, int len, const char** arg);
int ml_statespace_g_size(StateSpace_C *obj);

void ml_statespace_A_get(StateSpace_C *obj, char **result);
void ml_statespace_B_get(StateSpace_C *obj, char **result);
void ml_statespace_C_get(StateSpace_C *obj, char **result);
void ml_statespace_D_get(StateSpace_C *obj, char **result);

void ml_statespace_subs(StateSpace_C *obj,
                        int len,
                        const char **a,
                        const char **b);

void ml_statespace_linearize(StateSpace_C *obj);

void ml_statespace_ctrb(StateSpace_C *obj, char **result);
void ml_statespace_obsv(StateSpace_C *obj, char **result);

// // ----------------------------------------------------------------------
// // MDP wrapper functions.
// //
// typedef struct MDP_C MDP_C;
//
// MDP_C* ml_mdp_new(unsigned long x, unsigned long u);
// void ml_mdp_free(MDP_C* obj);
//
// int ml_mdp_num_states_get(MDP_C* obj);
//
// int ml_mdp_num_inputs_get(MDP_C* obj);
//
// void ml_mdp_probabilities_set(MDP_C *obj, const int *arg);
// void ml_mdp_probabilities_get(MDP_C *obj, int *result);
// void ml_mdp_probabilities_set_sparse(MDP_C *obj, unsigned long u,
//                                      unsigned long rlen, unsigned long clen,
//                                      unsigned long *r, unsigned long *c,
//                                      double *v);
// void ml_mdp_probabilities_get_sparse(MDP_C *obj, unsigned long u,
//                                      unsigned long *r, unsigned long *c,
//                                      double *v);
// unsigned long ml_mdp_probabilities_nnz(MDP_C *obj, unsigned long u);
//
// void ml_mdp_rewards_set(MDP_C *obj, const int *arg);
// void ml_mdp_rewards_get(MDP_C *obj, int *result);
// void ml_mdp_rewards_set_sparse(MDP_C *obj, unsigned long u,
//                                unsigned long rlen, unsigned long clen,
//                                unsigned long *r, unsigned long *c,
//                                double *v);
// void ml_mdp_rewards_get_sparse(MDP_C *obj, unsigned long u,
//                                unsigned long *r, unsigned long *c,
//                                double *v);
// unsigned long ml_mdp_rewards_nnz(MDP_C *obj, unsigned long u);
//
// double ml_mdp_gamma_get(MDP_C* obj);
// void ml_mdp_gamma_set(MDP_C* obj, double arg);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CONTROL_MATLAB_MATLAB_WRAPPER_HPP */
