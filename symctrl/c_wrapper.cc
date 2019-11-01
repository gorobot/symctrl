// ----------------------------------------------------------------------
// C Wrapper API Function Definitions
//

#include <iostream>
#include <functional>
#include <random>
#include <vector>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/cwrapper.h>
#include <symengine/subs.h>

#include "c_wrapper.hpp"

#include "analysis.hpp"
#include "subs.hpp"
// #include "matrix/eig.hpp"
// #include "matrix/linalg.hpp"

#include <symctrl/ode/ode.hpp>
#include <symctrl/math/math.hpp>

extern "C" {

#ifndef C_WRAPPER_RETURN_TYPE
#define C_WRAPPER_RETURN_TYPE int
#endif

#ifndef C_WRAPPER_NO_EXCEPTION
#define C_WRAPPER_NO_EXCEPTION 0
#endif

#ifndef C_WRAPPER_RUNTIME_EXCEPTION
#define C_WRAPPER_RUNTIME_EXCEPTION 1
#endif

#ifndef C_WRAPPER_BEGIN
#define C_WRAPPER_BEGIN try {
#endif

#ifndef C_WRAPPER_END
#define C_WRAPPER_END(Default) \
  } \
  catch(const std::exception &e) { \
    std::cerr << "An error occurred." << '\n'; \
    std::cerr << e.what() << '\n'; \
    return Default; \
  }
#endif

// ----------------------------------------------------------------------
// SymEngine Struct Definitions
//
struct CRCPBasic {
  SymEngine::RCP<const SymEngine::Basic> m;
};
struct CVecBasic {
    SymEngine::vec_basic m;
};
struct CDenseMatrix {
    SymEngine::DenseMatrix m;
};
struct CMapBasicBasic {
    SymEngine::map_basic_basic m;
};

// // ----------------------------------------------------------------------
// // Linear Algebra Function Definitions
// //
// void linalg_hessenberg(CDenseMatrix *A, CDenseMatrix *result) {
//   C_WRAPPER_BEGIN
//
//   Controls::hessenberg(A->m, result->m);
//
//   C_WRAPPER_END()
// }
//
// void linalg_schur(CDenseMatrix *A, CDenseMatrix *U, CDenseMatrix *T) {
//   C_WRAPPER_BEGIN
//
//   Controls::schur(A->m, U->m, T->m);
//
//   C_WRAPPER_END()
// }
//
// void linalg_eigenvalues(CDenseMatrix *A, CVecBasic *l, CDenseMatrix *v) {
//   C_WRAPPER_BEGIN
//
//   Controls::eigenvalues(A->m, l->m, v->m);
//
//   C_WRAPPER_END()
// }
//
// void linalg_first_eigenvalue(CDenseMatrix *A, CRCPBasic *l, double tol) {
//   C_WRAPPER_BEGIN
//
//   l->m = Controls::get_first_eigenvalue(A->m, tol);
//
//   C_WRAPPER_END()
// }

// ----------------------------------------------------------------------
// Analysis Function Definitions
//
void ctrb(CDenseMatrix *A, CDenseMatrix *B, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  Controls::ctrb(A->m, B->m, result->m);

  C_WRAPPER_END()
}
void obsv(CDenseMatrix *A, CDenseMatrix *C, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  Controls::obsv(A->m, C->m, result->m);

  C_WRAPPER_END()
}

// ----------------------------------------------------------------------
// StateSpace Function Definitions
//
struct StateSpace_C {
  Controls::StateSpace m;
};

StateSpace_C *statespace_new() {
  return new StateSpace_C;
}

void statespace_free(StateSpace_C *obj) {
  if(!obj) {
    return;
  }
  delete obj;
}

void statespace_states_push_back(StateSpace_C *obj, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.add_state(arg->m);

  C_WRAPPER_END()
}
void statespace_states_get(StateSpace_C *obj, size_t n, basic result) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  result->m = obj->m.get_state(n);

  C_WRAPPER_END()
}
void statespace_states_set(StateSpace_C *obj, size_t n, const basic arg) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  obj->m.set_state(n, arg->m);

  C_WRAPPER_END()
}
// void statespace_states_erase(StateSpace_C *obj, size_t n) {
//   C_WRAPPER_BEGIN
//
//   C_WRAPPER_END
// }
size_t statespace_states_size(StateSpace_C *obj) {
  return obj->m.get_num_states();
}

void statespace_inputs_push_back(StateSpace_C *obj, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.add_input(arg->m);

  C_WRAPPER_END()
}
void statespace_inputs_get(StateSpace_C *obj, size_t n, basic result) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  result->m = obj->m.get_input(n);

  C_WRAPPER_END()
}
void statespace_inputs_set(StateSpace_C *obj, size_t n, const basic arg) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  obj->m.set_input(n, arg->m);

  C_WRAPPER_END()
}
// void statespace_inputs_erase(StateSpace_C *obj, size_t n) {
//   C_WRAPPER_BEGIN
//
//   C_WRAPPER_END
// }
size_t statespace_inputs_size(StateSpace_C *obj) {
  return obj->m.get_num_inputs();
}

void statespace_f_push_back(StateSpace_C *obj, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.add_f(arg->m);

  C_WRAPPER_END()
}
void statespace_f_get(StateSpace_C *obj, size_t n, basic result) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  result->m = obj->m.get_f(n);

  C_WRAPPER_END()
}
void statespace_f_set(StateSpace_C *obj, size_t n, const basic arg) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  obj->m.set_f(n, arg->m);

  C_WRAPPER_END()
}
// void statespace_f_erase(StateSpace_C *obj, size_t n) {
//   C_WRAPPER_BEGIN
//
//   C_WRAPPER_END
// }
size_t statespace_f_size(StateSpace_C *obj) {
  return obj->m.get_num_f();
}

void statespace_g_push_back(StateSpace_C *obj, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.add_g(arg->m);

  C_WRAPPER_END()
}
void statespace_g_get(StateSpace_C *obj, size_t n, basic result) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  result->m = obj->m.get_g(n);

  C_WRAPPER_END()
}
void statespace_g_set(StateSpace_C *obj, size_t n, const basic arg) {
  C_WRAPPER_BEGIN

  // TODO: n < obj->m.size()
  obj->m.set_g(n, arg->m);

  C_WRAPPER_END()
}
// void statespace_g_erase(StateSpace_C *obj, size_t n) {
//   C_WRAPPER_BEGIN
//
//   C_WRAPPER_END
// }
size_t statespace_g_size(StateSpace_C *obj) {
  return obj->m.get_num_g();
}

void statespace_A_get(StateSpace_C *obj, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  obj->m.get_A_matrix(result->m);

  C_WRAPPER_END()
}
void statespace_B_get(StateSpace_C *obj, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  obj->m.get_B_matrix(result->m);

  C_WRAPPER_END()
}
void statespace_C_get(StateSpace_C *obj, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  obj->m.get_C_matrix(result->m);

  C_WRAPPER_END()
}
void statespace_D_get(StateSpace_C *obj, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  obj->m.get_D_matrix(result->m);

  C_WRAPPER_END()
}

void statespace_subs(StateSpace_C *obj, const basic k, const basic m) {
  C_WRAPPER_BEGIN

  Controls::subs(obj->m, k->m, m->m);

  C_WRAPPER_END()
}

void statespace_linearize(StateSpace_C *obj) {
  C_WRAPPER_BEGIN

  Controls::linearize(obj->m);

  C_WRAPPER_END()
}

void statespace_ctrb(StateSpace_C *obj, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  Controls::ctrb(obj->m, result->m);

  C_WRAPPER_END()
}

void statespace_obsv(StateSpace_C *obj, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  Controls::obsv(obj->m, result->m);

  C_WRAPPER_END()
}

// ----------------------------------------------------------------------
// TransferFunction Function Definitions
//
struct TransferFunction_C {
  Controls::TransferFunction m;
};

TransferFunction_C *transferfunction_new() {
  return new TransferFunction_C;
}

void transferfunction_free(TransferFunction_C *obj) {
  if(!obj) {
    return;
  }
  delete obj;
}

void transferfunction_var_get(TransferFunction_C *obj, basic result) {
  C_WRAPPER_BEGIN

  result->m = obj->m.get_var();

  C_WRAPPER_END()
}
void transferfunction_var_set(TransferFunction_C *obj, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.set_var(arg->m);

  C_WRAPPER_END()
}

void transferfunction_num_push_back(TransferFunction_C *obj, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.add_num(arg->m);

  C_WRAPPER_END()
}
void transferfunction_num_get(TransferFunction_C *obj, size_t n, basic result) {
  C_WRAPPER_BEGIN

  result->m = obj->m.get_num(n);

  C_WRAPPER_END()
}
void transferfunction_num_set(TransferFunction_C *obj, size_t n, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.set_num(n, arg->m);

  C_WRAPPER_END()
}
size_t transferfunction_num_size(TransferFunction_C *obj) {
  return obj->m.get_num_nums();
}

void transferfunction_den_push_back(TransferFunction_C *obj, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.add_den(arg->m);

  C_WRAPPER_END()
}
void transferfunction_den_get(TransferFunction_C *obj, size_t n, basic result) {
  C_WRAPPER_BEGIN

  result->m = obj->m.get_den(n);

  C_WRAPPER_END()
}
void transferfunction_den_set(TransferFunction_C *obj, size_t n, const basic arg) {
  C_WRAPPER_BEGIN

  obj->m.set_den(n, arg->m);

  C_WRAPPER_END()
}
size_t transferfunction_den_size(TransferFunction_C *obj) {
  return obj->m.get_num_dens();
}

// ----------------------------------------------------------------------
// CostFunction Function Definitions
//
struct StdFunction_C {
  // std::function<int(int)> m;
  int (*m)(int);
};

StdFunction_C *std_function_new(int (*arg)(int)) {
  auto s = new StdFunction_C;
  s->m = arg;
  return s;
  // return new StdFunction_C;
}
void std_function_free(StdFunction_C *obj) {
  if(!obj) {
    return;
  }
  delete obj;
}

// struct CostFunction_C {
//   Controls::CostFunction m;
// };
//
// CostFunction_C *cost_function_new() {
//   return new CostFunction_C;
// }
// void cost_function_free(CostFunction_C *obj) {
//   if(!obj) {
//     return;
//   }
//   delete obj;
// }

// ----------------------------------------------------------------------
// MDP Function Definitions
//
// struct MDP_C {
//   Controls::MDP m;
// };
//
// MDP_C *mdp_new() {
//   // return new MDP_C;
// }
// void mdp_free(MDP_C *obj) {
//   if(!obj) {
//     return;
//   }
//   delete obj;
// }

// size_t mdp_nstates(MDP_C *obj) {
//   return obj->m.nstates();
// }
//
// size_t mdp_ninputs(MDP_C *obj) {
//   return obj->m.ninputs();
// }
//
// void mdp_probabilities_set(MDP_C *obj, size_t u,
//                            size_t x, size_t xp, const double arg) {
//   //
//   C_WRAPPER_BEGIN
//
//   obj->m.set_probability(u, x, xp, arg);
//
//   C_WRAPPER_END()
// }
// double mdp_probabilities_get(MDP_C *obj, size_t u, size_t x, size_t xp) {
//   C_WRAPPER_BEGIN
//
//   return obj->m.get_probability(u, x, xp);
//
//   C_WRAPPER_END(0)
// }
// void mdp_probabilities_set_sparse(MDP_C *obj, size_t u,
//                                   size_t rlen, size_t clen,
//                                   size_t *r, size_t *c, double *v) {
//   C_WRAPPER_BEGIN
//
//   size_t n, m, idx = 0;
//   for(n = 0; n < rlen; n++) { // row
//     for(m = 0; m < clen; m++) { // col
//       obj->m.set_probability(u, r[n], c[m], v[idx++]);
//     }
//   }
//
//   C_WRAPPER_END()
// }
// void mdp_probabilities_get_sparse(MDP_C *obj, size_t u,
//                                   size_t **r, size_t **c, double **v) {
//   C_WRAPPER_BEGIN
//
//   if(obj->m.probabilities_.at(u).empty()) {
//     return;
//   }
//
//   size_t k = 0;
//   for(const auto &it : obj->m.probabilities_.at(u)) {
//     (*r)[k] = std::get<0>(it.first);
//     (*c)[k] = std::get<1>(it.first);
//     (*v)[k] = it.second;
//
//     k++;
//   }
//
//   C_WRAPPER_END()
// }
// // void mdp_probabilities_erase(MDP_C *obj, size_t n)
// size_t mdp_probabilities_nnz(MDP_C *obj, size_t u) {
//   C_WRAPPER_BEGIN
//
//   return obj->m.probabilities_.at(u).nnz();
//
//   C_WRAPPER_END(0)
// }
//
// void mdp_rewards_set(MDP_C *obj, size_t u,
//                      size_t x, size_t xp, const double arg) {
//   //
//   C_WRAPPER_BEGIN
//
//   obj->m.set_reward(u, x, xp, arg);
//
//   C_WRAPPER_END()
// }
// double mdp_rewards_get(MDP_C *obj, size_t u, size_t x, size_t xp) {
//   C_WRAPPER_BEGIN
//
//   return obj->m.get_reward(u, x, xp);
//
//   C_WRAPPER_END(0)
// }
// void mdp_rewards_set_sparse(MDP_C *obj, size_t u,
//                             size_t rlen, size_t clen,
//                             size_t *r, size_t *c, double *v) {
//   C_WRAPPER_BEGIN
//
//   size_t n, m, idx = 0;
//   for(n = 0; n < rlen; n++) { // row
//     for(m = 0; m < clen; m++) { // col
//       obj->m.set_reward(u, r[n], c[m], v[idx++]);
//     }
//   }
//
//   C_WRAPPER_END()
// }
// void mdp_rewards_get_sparse(MDP_C *obj, size_t u,
//                             size_t **r, size_t **c, double **v) {
//   C_WRAPPER_BEGIN
//
//   if(obj->m.rewards_.at(u).empty()) {
//     return;
//   }
//
//   size_t k = 0;
//   for(const auto &it : obj->m.rewards_.at(u)) {
//     (*r)[k] = std::get<0>(it.first);
//     (*c)[k] = std::get<1>(it.first);
//     (*v)[k] = it.second;
//
//     k++;
//   }
//
//   C_WRAPPER_END()
// }
// // void mdp_rewards_erase(MDP_C *obj, size_t n)
// size_t mdp_rewards_nnz(MDP_C *obj, size_t u) {
//   C_WRAPPER_BEGIN
//
//   return obj->m.rewards_.at(u).nnz();
//
//   C_WRAPPER_END(0)
// }
//
// double mdp_gamma_get(MDP_C *obj) {
//   return obj->m.get_gamma();
// }
// void mdp_gamma_set(MDP_C *obj, const double n) {
//   C_WRAPPER_BEGIN
//
//   obj->m.set_gamma(n);
//
//   C_WRAPPER_END()
// }

// ----------------------------------------------------------------------
// ODE Solver Function Definitions
//
struct OdeOptions_C {
  Controls::OdeOptions m;
};

OdeOptions_C *odeoptions_new() {
  return new OdeOptions_C;
}
void odeoptions_free(OdeOptions_C *obj) {
  if(!obj) {
    return;
  }
  delete obj;
}

double odeoptions_step_size_get(OdeOptions_C *obj) {
  C_WRAPPER_BEGIN

  return obj->m.get_step_size();

  C_WRAPPER_END(0.0)
}
void odeoptions_step_size_set(OdeOptions_C *obj,
                              const double arg) {
  C_WRAPPER_BEGIN

  obj->m.set_step_size(arg);

  C_WRAPPER_END()
}

void slv_ode_euler(StateSpace_C *obj,
                   const double *t_span,
                   const size_t t_span_len,
                   const double *x0,
                   const size_t x0_len,
                   double *t_result,
                   double *x_result,
                   OdeOptions_C *options) {
  //
  C_WRAPPER_BEGIN

  size_t i;

  std::vector<double> t_span_vec(t_span_len);
  for(i = 0; i < t_span_len; i++) {
    t_span_vec[i] = t_span[i];
  }

  std::vector<double> x0_vec(x0_len);
  for(i = 0; i < x0_len; i++) {
    x0_vec[i] = x0[i];
  }

  std::vector<double> t_result_vec;
  std::vector<double> x_result_vec;

  ode_euler(obj->m, t_span_vec, x0_vec, t_result_vec, x_result_vec, options->m);

  for(i = 0; i < t_result_vec.size(); i++) {
    t_result[i] = t_result_vec.at(i);
  }

  for(i = 0; i < x_result_vec.size(); i++) {
    x_result[i] = x_result_vec.at(i);
  }

  C_WRAPPER_END()
}

// ----------------------------------------------------------------------
// RandomDevice Function Definitions
//
struct RandomDevice_C {
  std::random_device *m;
};

RandomDevice_C *random_device_new() {
  return new RandomDevice_C;
}
void random_device_init(generator *obj) {
  obj->m = new std::random_device;
}
void random_device_free(generator *obj) {
  if(!obj) {
    return;
  }
  delete obj;
}

// ----------------------------------------------------------------------
// RandomDistribution Function Definitions
//
struct RandomDistribution_C {
  Controls::Math::RandomNumberDistribution *m;
};

RandomDistribution_C *random_number_distribution_new() {
  return new RandomDistribution_C;
}
void random_number_distribution_free(RandomDistribution_C *obj) {
  if(!obj) {
    return;
  }
  delete obj;
}

// #ifndef SYMCTRL_RANDOM_DISTRIBUTIONS_C
// #define SYMCTRL_RANDOM_DISTRIBUTIONS_C(MACRO) \
//   MACRO(uniform_int_distribution, const int a, const int b) \
//   MACRO(uniform_real_distribution, const double a, const double b) \
//   MACRO(bernoulli_distribution, const double p) \
//   MACRO(negative_binomial_distribution, const int k,
//   const double p) \
//   MACRO(geometric_distribution, const double p) \
//   MACRO(poisson_distribution, const double mean) \
//   MACRO(exponential_distribution, const double lambda) \
//   MACRO(gamma_distribution, const double alpha, const double beta) \
//   MACRO(weibull_distribution, const double a, const double b) \
//   MACRO(extreme_value_distribution, const double a, const double b) \
//   MACRO(normal_distribution, const double mean, const double stddev) \
//   MACRO(lognormal_distribution, const double m, const double s) \
//   MACRO(chi_squared_distribution, const double n) \
//   MACRO(cauchy_distribution, const double a, const double b) \
//   MACRO(fisher_f_distribution, const double m, const double n) \
//   MACRO(student_t_distribution, const double n)
// #endif
// //
// // #define CONST_ARGS(type, ...)
// // #define SYMCTRL_RANDOM_DISTRIBUTIONS_C_HEADER(name, ...) \
// // void ##name##_set(dist *obj, __VA_ARGS__)

void uniform_int_distribution_set(dist *obj, const int a, const int b) {
  obj->m = new Controls::Math::uniform_int_distribution<>(a, b);
}
void uniform_real_distribution_set(dist *obj, const double a, const double b) {
  obj->m = new Controls::Math::uniform_real_distribution<>(a, b);
}
void bernoulli_distribution_set(dist *obj, const double p) {
  // obj->m = new Controls::Math::bernoulli_distribution(p);
}
void negative_binomial_distribution_set(dist *obj,
                                        const int k,
                                        const double p) {
  obj->m = new Controls::Math::negative_binomial_distribution<>(k, p);
}
void geometric_distribution_set(dist *obj, const double p) {
  obj->m = new Controls::Math::geometric_distribution<>(p);
}
void poisson_distribution_set(dist *obj, const double mean) {
  obj->m = new Controls::Math::poisson_distribution<>(mean);
}
void exponential_distribution_set(dist *obj, const double lambda) {
  obj->m = new Controls::Math::exponential_distribution<>(lambda);
}
void gamma_distribution_set(dist *obj, const double alpha, const double beta) {
  obj->m = new Controls::Math::gamma_distribution<>(alpha, beta);
}
void weibull_distribution_set(dist *obj, const double a, const double b) {
  obj->m = new Controls::Math::weibull_distribution<>(a, b);
}
void extreme_value_distribution_set(dist *obj, const double a, const double b) {
  obj->m = new Controls::Math::extreme_value_distribution<>(a, b);
}
void normal_distribution_set(dist *obj, const double mean, const double stddev) {
  obj->m = new Controls::Math::normal_distribution<>(mean, stddev);
}
void lognormal_distribution_set(dist *obj, const double m, const double s) {
  obj->m = new Controls::Math::lognormal_distribution<>(m, s);
}
void chi_squared_distribution_set(dist *obj, const double n) {
  obj->m = new Controls::Math::chi_squared_distribution<>(n);
}
void cauchy_distribution_set(dist *obj, const double a, const double b) {
  obj->m = new Controls::Math::cauchy_distribution<>(a, b);
}
void fisher_f_distribution_set(dist *obj, const double m, const double n) {
  obj->m = new Controls::Math::fisher_f_distribution<>(m, n);
}
void student_t_distribution_set(dist *obj, const double n) {
  obj->m = new Controls::Math::student_t_distribution<>(n);
}

// ----------------------------------------------------------------------
// RandomVariable Function Definitions
//
struct RandomVariable_C {
  SymEngine::RCP<const Controls::Math::RandomVariable> m;
};

RandomVariable_C *random_variable_new() {
  return new RandomVariable_C();
}
void random_variable_free(RandomVariable_C *obj) {
  if(!obj) {
    return;
  }
  delete obj;
}

void random_variable_set(RandomVariable_C *obj,
                         const char *arg,
                         const RandomDistribution_C *d) {
  C_WRAPPER_BEGIN

  obj->m = Controls::Math::random_variable(std::string(arg), d->m);

  C_WRAPPER_END()
}

void random_variable_name_get(RandomVariable_C *obj, char **result) {
  C_WRAPPER_BEGIN

  std::string str = obj->m->__str__();
  auto cc = new char[str.length() + 1];
  std::strcpy(cc, str.c_str());
  result[0] = cc;

  C_WRAPPER_END()
}

double random_variable_sample(RandomVariable_C *obj, generator *gen) {
  C_WRAPPER_BEGIN

  return (*(obj->m)).sample(*(gen->m));

  C_WRAPPER_END(0)
}

// ---------------------------------------------------------------------------
// RandomVariable Replacement Function Definitions
//
void statespace_random_variable_replace(StateSpace_C *obj,
                                        const basic key,
                                        RandomVariable_C *mapped) {
  //
  C_WRAPPER_BEGIN

  CRCPBasic *s = new CRCPBasic();
  CRCPBasic *r = new CRCPBasic();
  CRCPBasic *mapp = new CRCPBasic();
  mapp->m = mapped->m;

  CMapBasicBasic *mapbb = new CMapBasicBasic();

  size_t sz, i;

  (mapbb->m)[key->m] = mapp->m;

  sz = statespace_f_size(obj);
  for(i = 0; i < sz; i++) {
    s->m = obj->m.get_f(i);

    r->m = s->m->subs(mapbb->m);

    obj->m.set_f(i, r->m);
  }

  delete mapbb;
  delete s;
  delete r;
  delete mapp;

  C_WRAPPER_END()
}

} // C
