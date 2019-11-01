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
// void ml_linalg_hessenberg(int len, char **A, char **result);
// void ml_linalg_schur(int len, char **A, char **U, char **T);
//
// void ml_linalg_eigenvalues(int len, char **A, char **l, char **v);
//
// void ml_linalg_first_eigenvalue(int len, char **A, char **l, double tol);

// ----------------------------------------------------------------------
// State space wrapper functions.
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

// ----------------------------------------------------------------------
// Transfer function wrapper functions.
//
typedef struct TransferFunction_C TransferFunction_C;

TransferFunction_C* ml_transferfunction_new();

void ml_transferfunction_free(TransferFunction_C *obj);

void ml_transferfunction_var_get(TransferFunction_C *obj, char **result);
void ml_transferfunction_var_set(TransferFunction_C *obj, const char** arg);

void ml_transferfunction_num_get(TransferFunction_C *obj, char **result);
void ml_transferfunction_num_set(TransferFunction_C *obj, int len, const char** arg);
int ml_transferfunction_num_size(TransferFunction_C *obj);

void ml_transferfunction_den_get(TransferFunction_C *obj, char **result);
void ml_transferfunction_den_set(TransferFunction_C *obj, int len, const char** arg);
int ml_transferfunction_den_size(TransferFunction_C *obj);

// ----------------------------------------------------------------------
// StdFunction wrapper functions.
//
typedef struct StdFunction_C StdFunction_C;

StdFunction_C* ml_std_function_new(int (*arg)(int));
void ml_std_function_free(StdFunction_C *obj);

// ----------------------------------------------------------------------
// MDP wrapper functions.
//
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

// ----------------------------------------------------------------------
// ODE solver wrapper functions.
//
typedef struct OdeOptions_C OdeOptions_C;

OdeOptions_C* ml_odeoptions_new();
void ml_odeoptions_free(OdeOptions_C *obj);

double ml_odeoptions_step_size_get(OdeOptions_C *obj);
void ml_odeoptions_step_size_set(OdeOptions_C *obj, const double arg);

void ml_slv_ode_euler(StateSpace_C *obj,
                      const double *t_span,
                      const int t_span_len,
                      const double *x0,
                      const int x0_len,
                      double *t_result,
                      double *x_result,
                      OdeOptions_C *options);
//

// ----------------------------------------------------------------------
// Random variable wrapper functions.
//
typedef struct RandomDevice_C RandomDevice_C;

RandomDevice_C *ml_random_device_new();
void ml_random_device_init(RandomDevice_C *obj);
void ml_random_device_free(RandomDevice_C *obj);

typedef struct RandomDistribution_C RandomDistribution_C;

RandomDistribution_C *ml_random_number_distribution_new();

void ml_uniform_int_distribution_set(RandomDistribution_C *obj,
                                     const int a,
                                     const int b);
void ml_uniform_real_distribution_set(RandomDistribution_C *obj,
                                      const double a,
                                      const double b);
// void ml_bernoulli_distribution_set(RandomDistribution_C *obj,
//                                    const double p);
void ml_negative_binomial_distribution_set(RandomDistribution_C *obj,
                                           const int k,
                                           const double p);
void ml_geometric_distribution_set(RandomDistribution_C *obj,
                                   const double p);
void ml_poisson_distribution_set(RandomDistribution_C *obj,
                                 const double mean);
void ml_exponential_distribution_set(RandomDistribution_C *obj,
                                     const double lambda);
void ml_gamma_distribution_set(RandomDistribution_C *obj,
                               const double alpha,
                               const double beta);
void ml_weibull_distribution_set(RandomDistribution_C *obj,
                                 const double a,
                                 const double b);
void ml_extreme_value_distribution_set(RandomDistribution_C *obj,
                                       const double a,
                                       const double b);
void ml_normal_distribution_set(RandomDistribution_C *obj,
                                const double mean,
                                const double stddev);
void ml_lognormal_distribution_set(RandomDistribution_C *obj,
                                   const double m,
                                   const double s);
void ml_chi_squared_distribution_set(RandomDistribution_C *obj,
                                     const double n);
void ml_cauchy_distribution_set(RandomDistribution_C *obj,
                                const double a,
                                const double b);
void ml_fisher_f_distribution_set(RandomDistribution_C *obj,
                                  const double m,
                                  const double n);
void ml_student_t_distribution_set(RandomDistribution_C *obj,
                                   const double n);

void ml_random_number_distribution_free(RandomDistribution_C *obj);

// typedef struct CRCPBasic CRCPBasic;
typedef struct RandomVariable_C RandomVariable_C;

RandomVariable_C *ml_random_variable_new(const char **arg,
                                         RandomDistribution_C *d);
void ml_random_variable_free(RandomVariable_C *obj);
void ml_random_variable_set(RandomVariable_C *obj,
                            const char **arg,
                            RandomDistribution_C *d);
// void ml_random_variable_distribution_set(RandomVariable_C *obj,
//                                          RandomDistribution_C *d);

void ml_random_variable_name_get(RandomVariable_C *obj, char **result);

double ml_random_variable_sample(RandomVariable_C *obj, RandomDevice_C *g);

// ----------------------------------------------------------------------
// Random variable replacement wrapper functions.
//
void ml_statespace_random_variable_replace(StateSpace_C *obj,
                                           const char** key,
                                           RandomVariable_C *mapped);

#ifdef __cplusplus
}
#endif

#endif // CONTROL_MATLAB_MATLAB_WRAPPER_HPP
