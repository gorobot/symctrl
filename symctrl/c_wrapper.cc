// ----------------------------------------------------------------------
// C Wrapper API Function Definitions
//

#include <iostream>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/cwrapper.h>
#include <symengine/subs.h>

#include "c_wrapper.hpp"

#include "analysis.hpp"
#include "subs.hpp"
#include "matrix/eig.hpp"
#include "matrix/linalg.hpp"

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

// ----------------------------------------------------------------------
// Linear Algebra Function Definitions
//
void linalg_hessenberg(CDenseMatrix *A, CDenseMatrix *result) {
  C_WRAPPER_BEGIN

  Controls::hessenberg(A->m, result->m);

  C_WRAPPER_END()
}

void linalg_schur(CDenseMatrix *A, CDenseMatrix *U, CDenseMatrix *T) {
  C_WRAPPER_BEGIN

  Controls::schur(A->m, U->m, T->m);

  C_WRAPPER_END()
}

void linalg_eigenvalues(CDenseMatrix *A, CVecBasic *l, CDenseMatrix *v) {
  C_WRAPPER_BEGIN

  Controls::eigenvalues(A->m, l->m, v->m);

  C_WRAPPER_END()
}

void linalg_first_eigenvalue(CDenseMatrix *A, CRCPBasic *l, double tol) {
  C_WRAPPER_BEGIN

  l->m = Controls::get_first_eigenvalue(A->m, tol);

  C_WRAPPER_END()
}

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

// // ----------------------------------------------------------------------
// // MDP Function Definitions
// //
// struct MDP_C {
//   Controls::MDP m;
// };
//
// // struct SparseMatrix_key {
// //   sparse_key_t k
// // };
// // typedef struct SparseMatrix_key SparseMatrix_key;
// //
// // struct SparseMatrix_C {
// //   SparseMatrix<double> m;
// // };
// // typedef struct SparseMatrix_C SparseMatrix_C;
//
// MDP_C *mdp_new(const size_t x, const size_t u) {
//   return new MDP_C({{x, u}});
// }
// 
// void mdp_free(MDP_C *obj) {
//   if(!obj) {
//     return;
//   }
//   delete obj;
// }
//
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
// TransferFunction Function Definitions
//
struct TransferFunction_C {
  Controls::TransferFunction m;
};

// TransferFunction_C* transferfunction_new() {
//   return new TransferFunction_C;
// }
//
// void transferfunction_free(TransferFunction_C* obj) {
//   if(!obj) {
//     return;
//   }
//   delete obj;
// }

} // C
