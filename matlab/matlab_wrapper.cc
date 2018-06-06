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

#include "libsymctrl/c_wrapper.hpp"

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
void ml_la_compute_hessenberg(int len, char **arg, char **result) {
  auto mat = dense_matrix_new_rows_cols(len, len);
  auto res = dense_matrix_new_rows_cols(len, len);
  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for (i = 0; i < len; i++) {
    for (j = 0; j < len; j++) {
      basic_parse(s, arg[idx++]);
      dense_matrix_set_basic(mat, i, j, s);
    }
  }

  la_compute_hessenberg(mat, res);

  idx = 0;
  for(i = 0; i < len; i++) { // rows
    for (j = 0; j < len; j++) { // cols
      dense_matrix_get_basic(s, res, j, i);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = se_parse(basic_str(s));
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
  dense_matrix_free(res);
}

void ml_la_compute_schur(int len, char **A, char **U, char **T) {
  auto mat = dense_matrix_new_rows_cols(len, len);
  auto res_U = dense_matrix_new_rows_cols(len, len);
  auto res_T = dense_matrix_new_rows_cols(len, len);
  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for (i = 0; i < len; i++) {
    for (j = 0; j < len; j++) {
      basic_parse(s, A[idx++]);
      dense_matrix_set_basic(mat, i, j, s);
    }
  }

  la_compute_schur(mat, res_U, res_T);

  idx = 0;
  for(i = 0; i < len; i++) { // rows
    for (j = 0; j < len; j++) { // cols
      dense_matrix_get_basic(s, res_U, j, i);
      U[idx] = se_parse(basic_str(s));

      dense_matrix_get_basic(s, res_T, j, i);
      T[idx] = se_parse(basic_str(s));

      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
  dense_matrix_free(res_U);
  dense_matrix_free(res_T);
}

void ml_la_compute_eigenvalues(int len, char **A, char **l, char **v) {
  auto mat = dense_matrix_new_rows_cols(len, len);
  auto res_l = vecbasic_new();
  auto res_v = dense_matrix_new_rows_cols(len, len);
  auto s = basic_new_heap();

  int i = 0;
  int j = 0;
  int idx = 0;
  for (i = 0; i < len; i++) {
    for (j = 0; j < len; j++) {
      basic_parse(s, A[idx++]);
      dense_matrix_set_basic(mat, i, j, s);
    }
  }

  la_compute_eigenvalues(mat, res_l, res_v);

  idx = 0;
  for(i = 0; i < len; i++) { // rows
    vecbasic_get(res_l, i, s);
    l[i] = se_parse(basic_str(s));

    for (j = 0; j < len; j++) { // cols
      dense_matrix_get_basic(s, res_v, j, i);
      v[idx] = se_parse(basic_str(s));

      idx++;
    }
  }

  basic_free_heap(s);
  vecbasic_free(res_l);
  dense_matrix_free(res_v);
}

// ----------------------------------------------------------------------
// State Space wrapper functions.
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
    result[i] = basic_str(s);
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
    } else {
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
    result[i] = basic_str(s);
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
    } else {
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
    result[i] = basic_str(s);
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
    } else {
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
    result[i] = basic_str(s);
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
    } else {
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
      result[idx] = basic_str(s);
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
  for(i = 0; i < n; i++) { // rows
    for (j = 0; j < m; j++) { // cols
      dense_matrix_get_basic(s, mat, i, j);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = basic_str(s);
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
      result[idx] = basic_str(s);
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
      dense_matrix_get_basic(s, mat, i, j);
      // TODO: Convert string here to Matlab Symbolic format.
      result[idx] = basic_str(s);
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
      result[idx] = basic_str(s);
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
      result[idx] = basic_str(s);
      idx++;
    }
  }

  basic_free_heap(s);
  dense_matrix_free(mat);
}

// ----------------------------------------------------------------------
// MDP wrapper functions.
//
MDP_C* ml_mdp_new() {
  return mdp_new();
}

void ml_mdp_free(MDP_C* obj) {
  mdp_free(obj);
}

int ml_mdp_get_num_states(MDP_C* obj) {
  return mdp_num_states_get(obj);
}
void ml_mdp_set_num_states(MDP_C* obj, int arg) {
  mdp_num_states_set(obj, arg);
}

int ml_mdp_get_num_inputs(MDP_C* obj) {
  return mdp_num_inputs_get(obj);
}
void ml_mdp_set_num_inputs(MDP_C* obj, int arg) {
  mdp_num_inputs_set(obj, arg);
}

void ml_mdp_probabilities_set(MDP_C *obj,
                              size_t u,
                              size_t x,
                              size_t xp,
                              const double arg) {
  mdp_probabilities_set(obj, u, x, xp, arg);
}
double ml_mdp_probabilities_get(MDP_C *obj,
                                size_t u,
                                size_t x,
                                size_t xp) {
  return mdp_probabilities_get(obj, u, x, xp);
}
void ml_mdp_rewards_set(MDP_C *obj,
                        size_t u,
                        size_t x,
                        size_t xp,
                        const double arg) {
  mdp_rewards_set(obj, u, x, xp, arg);
}
double ml_mdp_rewards_get(MDP_C *obj,
                          size_t u,
                          size_t x,
                          size_t xp) {
  return mdp_rewards_get(obj, u, x, xp);
}

double ml_mdp_get_gamma(MDP_C* obj) {
  return mdp_gamma_get(obj);
}
void ml_mdp_set_gamma(MDP_C* obj, double arg) {
  mdp_gamma_set(obj, arg);
}


} // C
