// ----------------------------------------------------------------------
// Matlab Wrapper API Function Definitions
//
// Most of the function wrappers in the Matlab wrappers are designed to
// implement Matlab's matrix syntax. All variables in Matlab are defined as
// vectors and matrices, meaning we need to implement a lot of for loops and **
// pointers in order to make the C wrappers work with Matlab.

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <symengine/basic.h>
#include <symengine/matrix.h>
#include <symengine/cwrapper.h>

// For C. C Matrix API.
#include <mex.h>
#include <matrix.h>
// For C++. MATLAB Data API.
// #include <MatlabDataArray.hpp>

#include "matlab_wrapper.hpp"

#include "symctrl/c_wrapper.hpp"

// Re-define here from SymEngine API.

// struct CRCPBasic {
//   SymEngine::RCP<const SymEngine::Basic> m;
// };
// struct CVecBasic {
//     SymEngine::vec_basic m;
// };
// struct CDenseMatrix {
//     SymEngine::DenseMatrix m;
// };

// ----------------------------------------------------------------------
// Convert SymEngine to Matlab Symbolic and vice-versa.
//
// mxArray* se2sym(SymEngine::RCP<const SymEngine::Basic> arg) {
//   mxArray* matlab_sym;
//
//   return matlab_sym;
// }
//
// SymEngine::RCP<const SymEngine::Basic> sym2se(mxArray* arg) {
//   SymEngine::RCP<const SymEngine::Basic> symengine_sym;
//
//   return symengine_sym;
// }
char* se_parse(char *c) {
  std::string str = c;
  std::string fnd = "**";
  std::string rep = "^";
  // Replace common tokens.
  // std::replace(str.begin(), str.end(), "**", "^");
  for(std::string::size_type i = 0;
      (i = str.find(fnd, i)) != std::string::npos;) {
    str.replace(i, fnd.length(), rep);
    i += rep.length();
  }
  auto cc = new char[str.length() + 1];
  std::strcpy(cc, str.c_str());
  return cc;
}

extern "C" {

// ----------------------------------------------------------------------
// Linear algebra wrapper functions.
//
// void ml_linalg_hessenberg(int len, char **arg, char **result) {
//   auto mat = dense_matrix_new_rows_cols(len, len);
//   auto res = dense_matrix_new_rows_cols(len, len);
//   auto s = basic_new_heap();
//
//   int i = 0;
//   int j = 0;
//   int idx = 0;
//   for (i = 0; i < len; i++) {
//     for (j = 0; j < len; j++) {
//       basic_parse(s, arg[idx++]);
//       dense_matrix_set_basic(mat, j, i, s);
//     }
//   }
//
//   linalg_hessenberg(mat, res);
//
//   idx = 0;
//   for(i = 0; i < len; i++) { // rows
//     for (j = 0; j < len; j++) { // cols
//       dense_matrix_get_basic(s, res, j, i);
//       // TODO: Convert string here to Matlab Symbolic format.
//       result[idx] = se_parse(basic_str(s));
//       idx++;
//     }
//   }
//
//   basic_free_heap(s);
//   dense_matrix_free(mat);
//   dense_matrix_free(res);
// }
//
// void ml_linalg_schur(int len, char **A, char **U, char **T) {
//   auto mat = dense_matrix_new_rows_cols(len, len);
//   auto res_U = dense_matrix_new_rows_cols(len, len);
//   auto res_T = dense_matrix_new_rows_cols(len, len);
//   auto s = basic_new_heap();
//
//   int i = 0;
//   int j = 0;
//   int idx = 0;
//   for (i = 0; i < len; i++) {
//     for (j = 0; j < len; j++) {
//       basic_parse(s, A[idx++]);
//       dense_matrix_set_basic(mat, j, i, s);
//     }
//   }
//
//   linalg_schur(mat, res_U, res_T);
//
//   idx = 0;
//   for(i = 0; i < len; i++) { // rows
//     for (j = 0; j < len; j++) { // cols
//       dense_matrix_get_basic(s, res_U, j, i);
//       U[idx] = se_parse(basic_str(s));
//
//       dense_matrix_get_basic(s, res_T, j, i);
//       T[idx] = se_parse(basic_str(s));
//
//       idx++;
//     }
//   }
//
//   basic_free_heap(s);
//   dense_matrix_free(mat);
//   dense_matrix_free(res_U);
//   dense_matrix_free(res_T);
// }
//
// void ml_linalg_eigenvalues(int len, char **A, char **l, char **v) {
//   auto mat = dense_matrix_new_rows_cols(len, len);
//   auto res_l = vecbasic_new();
//   auto res_v = dense_matrix_new_rows_cols(len, len);
//   auto s = basic_new_heap();
//
//   int i = 0;
//   int j = 0;
//   int idx = 0;
//   for (i = 0; i < len; i++) {
//     for (j = 0; j < len; j++) {
//       basic_parse(s, A[idx++]);
//       dense_matrix_set_basic(mat, i, j, s);
//     }
//   }
//
//   linalg_eigenvalues(mat, res_l, res_v);
//
//   idx = 0;
//   for(i = 0; i < len; i++) { // rows
//     vecbasic_get(res_l, i, s);
//     l[i] = se_parse(basic_str(s));
//
//     for (j = 0; j < len; j++) { // cols
//       dense_matrix_get_basic(s, res_v, j, i);
//       v[idx] = se_parse(basic_str(s));
//
//       idx++;
//     }
//   }
//
//   basic_free_heap(s);
//   vecbasic_free(res_l);
//   dense_matrix_free(res_v);
// }
//
// void ml_linalg_first_eigenvalue(int len, char **A, char **l, double tol) {
//   auto mat = dense_matrix_new_rows_cols(len, len);
//   auto s = basic_new_heap();
//
//   int i = 0;
//   int j = 0;
//   int idx = 0;
//   for (i = 0; i < len; i++) {
//     for (j = 0; j < len; j++) {
//       basic_parse(s, A[idx++]);
//       dense_matrix_set_basic(mat, i, j, s);
//     }
//   }
//
//   linalg_first_eigenvalue(mat, s, tol);
//
//   l[0] = se_parse(basic_str(s));
//   // dense_matrix_set_basic(l, 0, 0, se_parse(basic_str(s)));
//
//   basic_free_heap(s);
//   dense_matrix_free(mat);
//   // dense_matrix_free(res);
// }

// ----------------------------------------------------------------------
// State space wrapper functions.
//
StateSpace_C* ml_statespace_new() {
  return statespace_new();
}

void ml_statespace_free(StateSpace_C *obj) {
  statespace_free(obj);
}

void ml_statespace_states_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_states_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < sz; i++) {
    statespace_states_get(obj, i, s);
    // TODO: Convert string here to Matlab Symbolic format.
    result[i] = se_parse(basic_str(s));
  }
  basic_free_heap(s);
}
void ml_statespace_states_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_states_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      statespace_states_push_back(obj, s);
    }
    else {
      statespace_states_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_statespace_states_size(StateSpace_C *obj) {
  return statespace_states_size(obj);
}

void ml_statespace_inputs_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_inputs_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < sz; i++) {
    statespace_inputs_get(obj, i, s);
    // TODO: Convert string here to Matlab Symbolic format.
    result[i] = se_parse(basic_str(s));
  }
  basic_free_heap(s);
}
void ml_statespace_inputs_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_inputs_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      statespace_inputs_push_back(obj, s);
    }
    else {
      statespace_inputs_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_statespace_inputs_size(StateSpace_C *obj) {
  return statespace_inputs_size(obj);
}

void ml_statespace_f_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_f_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < sz; i++) {
    statespace_f_get(obj, i, s);
    // TODO: Convert string here to Matlab Symbolic format.
    result[i] = se_parse(basic_str(s));
  }
  basic_free_heap(s);
}
void ml_statespace_f_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_f_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      statespace_f_push_back(obj, s);
    }
    else {
      statespace_f_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_statespace_f_size(StateSpace_C *obj) {
  return statespace_f_size(obj);
}

void ml_statespace_g_get(StateSpace_C *obj, char **result) {
  size_t sz = statespace_g_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < sz; i++) {
    statespace_g_get(obj, i, s);
    // TODO: Convert string here to Matlab Symbolic format.
    result[i] = se_parse(basic_str(s));
  }
  basic_free_heap(s);
}
void ml_statespace_g_set(StateSpace_C *obj, int len, const char** arg) {
  size_t sz = statespace_g_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      statespace_g_push_back(obj, s);
    }
    else {
      statespace_g_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_statespace_g_size(StateSpace_C *obj) {
  return statespace_g_size(obj);
}

// Get state matrix.
void ml_statespace_A_get(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t fn = statespace_f_size(obj);

  // Matrix dimensions must be square.
  if(n == 0 || n != fn) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(n, n);
  statespace_A_get(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < n; i++) { // rows
    for (j = 0; j < n; j++) { // cols
      dense_matrix_get_basic(s, mat, j, i);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = se_parse(basic_str(s));
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// Get input matrix.
void ml_statespace_B_get(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t m = statespace_inputs_size(obj);
  size_t fn = statespace_f_size(obj);

  // Number of inputs must be greater than 0.
  if(n == 0 || m == 0 || n != fn) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(n, m);
  statespace_B_get(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < m; i++) { // rows
    for (j = 0; j < n; j++) { // cols
      dense_matrix_get_basic(s, mat, j, i);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = se_parse(basic_str(s));
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// Get output matrix.
void ml_statespace_C_get(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t p = statespace_g_size(obj);

  // Number of output equations must be greater than 0.
  if(n == 0 || p == 0) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(p, n);
  statespace_C_get(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < p; i++) { // rows
    for (j = 0; j < n; j++) { // cols
      dense_matrix_get_basic(s, mat, i, j);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = se_parse(basic_str(s));
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// Get feed-through matrix.
void ml_statespace_D_get(StateSpace_C *obj, char **result) {
  size_t m = statespace_inputs_size(obj);
  size_t p = statespace_g_size(obj);

  // Number of inputs & output equations must be greater than 0.
  if(m == 0 || p == 0) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(p, m);
  statespace_D_get(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < p; i++) { // rows
    for (j = 0; j < m; j++) { // cols
      dense_matrix_get_basic(s, mat, j, i);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = se_parse(basic_str(s));
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

void ml_statespace_subs(StateSpace_C *obj,
                        int len,
                        const char **a,
                        const char **b) {

  // TODO: Exception handling.
  auto s_key = basic_new_heap();
  auto s_map = basic_new_heap();

  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert argument to SymEngine format.
    basic_parse(s_key, a[i]);
    basic_parse(s_map, b[i]);

    statespace_subs(obj, s_key, s_map);
  }

  basic_free_heap(s_key);
  basic_free_heap(s_map);
}

void ml_statespace_linearize(StateSpace_C *obj) {
  statespace_linearize(obj);
}

// Get controllability matrix.
void ml_statespace_ctrb(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t m = statespace_inputs_size(obj);
  size_t fn = statespace_f_size(obj);

  // Matrix dimensions must be square.
  if(n == 0 || m == 0 || n != fn) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(n, n*m);
  statespace_ctrb(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < n*m; i++) { // rows
    for(j = 0; j < n; j++) { // cols
      dense_matrix_get_basic(s, mat, j, i);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = se_parse(basic_str(s));
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// Get observability matrix.
void ml_statespace_obsv(StateSpace_C *obj, char **result) {
  size_t n = statespace_states_size(obj);
  size_t fn = statespace_f_size(obj);
  size_t p = statespace_g_size(obj);

  // Matrix dimensions must be square.
  if(n == 0 || p == 0 || n != fn) {
    return;
  }

  auto mat = dense_matrix_new_rows_cols(n*p, n);
  statespace_obsv(obj, mat);

  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for(i = 0; i < n; i++) { // rows
    for(j = 0; j < n*p; j++) { // cols
      dense_matrix_get_basic(s, mat, j, i);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = se_parse(basic_str(s));
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// ----------------------------------------------------------------------
// Transfer function wrapper functions.
//
TransferFunction_C* ml_transferfunction_new() {
  return transferfunction_new();
}

void ml_transferfunction_free(TransferFunction_C *obj) {
  transferfunction_free(obj);
}

void ml_transferfunction_var_get(TransferFunction_C *obj, char **result) {
  auto s = basic_new_heap();
  transferfunction_var_get(obj, s);
  result[0] = se_parse(basic_str(s));
  basic_free_heap(s);
}
void ml_transferfunction_var_set(TransferFunction_C *obj, const char** arg) {
  auto s = basic_new_heap();
  basic_parse(s, arg[0]);
  transferfunction_var_set(obj, s);
  basic_free_heap(s);
}

void ml_transferfunction_num_get(TransferFunction_C *obj, char **result) {
  size_t sz = transferfunction_num_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for (i = 0; i < sz; i++) {
    transferfunction_num_get(obj, i, s);
    result[i] = se_parse(basic_str(s));
  }
  basic_free_heap(s);
}
void ml_transferfunction_num_set(TransferFunction_C *obj, int len, const char** arg) {
  size_t sz = transferfunction_num_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      transferfunction_num_push_back(obj, s);
    }
    else {
      transferfunction_num_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_transferfunction_num_size(TransferFunction_C *obj) {
  return transferfunction_num_size(obj);
}

void ml_transferfunction_den_get(TransferFunction_C *obj, char **result) {
  size_t sz = transferfunction_den_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for (i = 0; i < sz; i++) {
    transferfunction_den_get(obj, i, s);
    result[i] = se_parse(basic_str(s));
  }
  basic_free_heap(s);
}
void ml_transferfunction_den_set(TransferFunction_C *obj, int len, const char** arg) {
  size_t sz = transferfunction_den_size(obj);
  auto s = basic_new_heap();
  int i = 0;
  for(i = 0; i < len; i++) {
    // TODO: Convert arg[i] here to SymEngine format. Pass the formatted string.
    basic_parse(s, arg[i]);

    if(i >= sz) {
      transferfunction_den_push_back(obj, s);
    }
    else {
      transferfunction_den_set(obj, i, s);
    }
  }
  basic_free_heap(s);
}
int ml_transferfunction_den_size(TransferFunction_C *obj) {
  return transferfunction_den_size(obj);
}

// ----------------------------------------------------------------------
// StdFunction wrapper functions.
//
StdFunction_C* ml_std_function_new(int (*arg)(int)) {
  return std_function_new(arg);
}
void ml_std_function_free(StdFunction_C *obj) {
  std_function_free(obj);
}

// // ----------------------------------------------------------------------
// // MDP wrapper functions.
// //
// MDP_C* ml_mdp_new(unsigned long x, unsigned long u) {
//   return mdp_new(x, u);
// }
//
// void ml_mdp_free(MDP_C* obj) {
//   mdp_free(obj);
// }
//
// int ml_mdp_num_states_get(MDP_C* obj) {
//   return mdp_num_states_get(obj);
// }
//
// int ml_mdp_num_inputs_get(MDP_C* obj) {
//   return mdp_num_inputs_get(obj);
// }
//
// void ml_mdp_probabilities_set(MDP_C *obj, const int *arg) {
//   size_t i, j, k, u, x;
//   u = mdp_num_inputs_get(obj);
//   x = mdp_num_states_get(obj);
//
//   for(i = 0; i < u; i++) {
//     for(j = 0; j < x; j++) {
//       for(k = 0; k < x; k++) {
//         mdp_probabilities_set(obj, i, j, k, *arg++);
//       }
//     }
//   }
// }
// void ml_mdp_probabilities_get(MDP_C *obj, int *result) {
//   size_t i, j, k, u, x;
//   u = mdp_num_inputs_get(obj);
//   x = mdp_num_states_get(obj);
//
//   for(i = 0; i < u; i++) {
//     for(j = 0; j < x; j++) {
//       for(k = 0; k < x; k++) {
//         *result++ = mdp_probabilities_get(obj, i, j, k);
//       }
//     }
//   }
// }
// void ml_mdp_probabilities_set_sparse(MDP_C *obj, unsigned long u,
//                                      unsigned long rlen, unsigned long clen,
//                                      unsigned long *r, unsigned long *c,
//                                      double *v) {
//   //
//   mdp_probabilities_set_sparse(obj, u, rlen, clen, r, c, v);
// }
// void ml_mdp_probabilities_get_sparse(MDP_C *obj, unsigned long u,
//                                      unsigned long *r, unsigned long *c,
//                                      double *v) {
//   //
//   mdp_probabilities_get_sparse(obj, u, &r, &c, &v);
// }
// unsigned long ml_mdp_probabilities_nnz(MDP_C *obj, unsigned long u) {
//   return mdp_probabilities_nnz(obj, u);
// }
//
// void ml_mdp_rewards_set(MDP_C *obj, const int *arg) {
//   size_t i, j, k, u, x;
//   u = mdp_num_inputs_get(obj);
//   x = mdp_num_states_get(obj);
//
//   for(i = 0; i < u; i++) {
//     for(j = 0; j < x; j++) {
//       for(k = 0; k < x; k++) {
//         mdp_rewards_set(obj, i, j, k, *arg++);
//       }
//     }
//   }
//   // mdp_rewards_set(obj, u, x, xp, arg);
// }
// void ml_mdp_rewards_get(MDP_C *obj, int *result) {
//   size_t i, j, k, u, x;
//   u = mdp_num_inputs_get(obj);
//   x = mdp_num_states_get(obj);
//
//   for(i = 0; i < u; i++) {
//     for(j = 0; j < x; j++) {
//       for(k = 0; k < x; k++) {
//         *result++ = mdp_rewards_get(obj, i, j, k);
//       }
//     }
//   }
//   // return mdp_rewards_get(obj, u, x, xp);
// }
// void ml_mdp_rewards_set_sparse(MDP_C *obj, unsigned long u,
//                                unsigned long rlen, unsigned long clen,
//                                unsigned long *r, unsigned long *c,
//                                double *v) {
//   //
//   mdp_rewards_set_sparse(obj, u, rlen, clen, r, c, v);
// }
// void ml_mdp_rewards_get_sparse(MDP_C *obj, unsigned long u,
//                                unsigned long *r, unsigned long *c,
//                                double *v) {
//   //
//   mdp_rewards_get_sparse(obj, u, &r, &c, &v);
// }
// unsigned long ml_mdp_rewards_nnz(MDP_C *obj, unsigned long u) {
//   return mdp_rewards_nnz(obj, u);
// }
//
// double ml_mdp_gamma_get(MDP_C* obj) {
//   return mdp_gamma_get(obj);
// }
// void ml_mdp_gamma_set(MDP_C* obj, double arg) {
//   mdp_gamma_set(obj, arg);
// }

// ----------------------------------------------------------------------
// ODE solver wrapper functions.
//
OdeOptions_C* ml_odeoptions_new() {
  return odeoptions_new();
}
void ml_odeoptions_free(OdeOptions_C *obj) {
  odeoptions_free(obj);
}

double ml_odeoptions_step_size_get(OdeOptions_C *obj) {
  return odeoptions_step_size_get(obj);
}
void ml_odeoptions_step_size_set(OdeOptions_C *obj, const double arg) {
  odeoptions_step_size_set(obj, arg);
}

void ml_slv_ode_euler(StateSpace_C *obj,
                      const double *t_span,
                      const int t_span_len,
                      const double *x0,
                      const int x0_len,
                      double *t_result,
                      double *x_result,
                      OdeOptions_C *options) {
  //
  slv_ode_euler(obj, t_span, t_span_len, x0, x0_len,
                t_result, x_result, options);
}

// ----------------------------------------------------------------------
// Random variable wrapper functions.
//
RandomDevice_C *ml_random_device_new() {
  return random_device_new();
}
void ml_random_device_init(RandomDevice_C *obj) {
  random_device_init(obj);
}
void ml_random_device_free(RandomDevice_C *obj) {
  random_device_free(obj);
}

RandomDistribution_C *ml_random_number_distribution_new() {
  return random_number_distribution_new();
}

void ml_uniform_int_distribution_set(RandomDistribution_C *obj,
                                     const int a,
                                     const int b) {
  uniform_int_distribution_set(obj, a, b);
}
void ml_uniform_real_distribution_set(RandomDistribution_C *obj,
                                      const double a,
                                      const double b) {
  uniform_real_distribution_set(obj, a, b);
}
// void ml_bernoulli_distribution_set(RandomDistribution_C *obj,
//                                    const double p) {
//   bernoulli_distribution_set(obj, p);
// }
void ml_negative_binomial_distribution_set(RandomDistribution_C *obj,
                                           const int k,
                                           const double p) {
  negative_binomial_distribution_set(obj, k, p);
}
void ml_geometric_distribution_set(RandomDistribution_C *obj,
                                   const double p) {
  geometric_distribution_set(obj, p);
}
void ml_poisson_distribution_set(RandomDistribution_C *obj,
                                 const double mean) {
  poisson_distribution_set(obj, mean);
}
void ml_exponential_distribution_set(RandomDistribution_C *obj,
                                     const double lambda) {
  exponential_distribution_set(obj, lambda);
}
void ml_gamma_distribution_set(RandomDistribution_C *obj,
                               const double alpha,
                               const double beta) {
  gamma_distribution_set(obj, alpha, beta);
}
void ml_weibull_distribution_set(RandomDistribution_C *obj,
                                 const double a,
                                 const double b) {
  weibull_distribution_set(obj, a, b);
}
void ml_extreme_value_distribution_set(RandomDistribution_C *obj,
                                       const double a,
                                       const double b) {
  extreme_value_distribution_set(obj, a, b);
}
void ml_normal_distribution_set(RandomDistribution_C *obj,
                                const double mean,
                                const double stddev) {
  normal_distribution_set(obj, mean, stddev);
}
void ml_lognormal_distribution_set(RandomDistribution_C *obj,
                                   const double m,
                                   const double s) {
  lognormal_distribution_set(obj, m, s);
}
void ml_chi_squared_distribution_set(RandomDistribution_C *obj,
                                     const double n) {
  chi_squared_distribution_set(obj, n);
}
void ml_cauchy_distribution_set(RandomDistribution_C *obj,
                                const double a,
                                const double b) {
  cauchy_distribution_set(obj, a, b);
}
void ml_fisher_f_distribution_set(RandomDistribution_C *obj,
                                  const double m,
                                  const double n) {
  fisher_f_distribution_set(obj, m, n);
}
void ml_student_t_distribution_set(RandomDistribution_C *obj,
                                   const double n) {
  student_t_distribution_set(obj, n);
}

void ml_random_number_distribution_free(RandomDistribution_C *obj) {
  random_number_distribution_free(obj);
}

RandomVariable_C *ml_random_variable_new(const char **arg,
                                         RandomDistribution_C *d) {
  auto s = random_variable_new();
  random_variable_set(s, *arg, d);
  return s;
}
void ml_random_variable_free(RandomVariable_C *obj) {
  random_variable_free(obj);
}
void ml_random_variable_set(RandomVariable_C *obj,
                            const char **arg,
                            RandomDistribution_C *d) {
  random_variable_set(obj, *arg, d);
}
// void ml_random_variable_distribution_set(RandomVariable_C *obj,
//                                          RandomDistribution_C *d) {
//   random_variable_distribution_set(obj, d);
// }

void ml_random_variable_name_get(RandomVariable_C *obj, char **result) {
  // result[0] = se_parse(basic_str(obj));
  // random_variable_name_get(obj, *result);
  // std::string str = obj->m->__str__();
  // auto cc = new char[str.length() + 1];
  // std::strcpy(cc, str.c_str());
  // result[0] = se_parse(cc);
  random_variable_name_get(obj, result);
}

double ml_random_variable_sample(RandomVariable_C *obj, RandomDevice_C *g) {
  return random_variable_sample(obj, g);
}

// ----------------------------------------------------------------------
// Random variable replacement wrapper functions.
//
void ml_statespace_random_variable_replace(StateSpace_C *obj,
                                           const char** key,
                                           RandomVariable_C *mapped) {
  //
  auto k = basic_new_heap();
  basic_parse(k, key[0]);
  statespace_random_variable_replace(obj, k, mapped);
  basic_free_heap(k);
}

} // C
