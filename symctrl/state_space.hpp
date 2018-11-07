#ifndef SYMCTRL_STATE_SPACE_HPP
#define SYMCTRL_STATE_SPACE_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

#include "system.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// StateSpace
//
class StateSpace : public System {
public:
  StateSpace();
  StateSpace(SymEngine::MatrixBase &A,
             SymEngine::MatrixBase &B,
             SymEngine::MatrixBase &C,
             SymEngine::MatrixBase &D);
  ~StateSpace();

  void add_state(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_state(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_state(size_t n);
  // void remove_state(size_t n);
  size_t get_num_states();

  void add_input(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_input(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_input(size_t n);
  // void remove_input(size_t n);
  size_t get_num_inputs();

  void add_f(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_f(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_f(size_t n);
  // void remove_f(size_t n);
  size_t get_num_f();

  void add_g(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_g(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_g(size_t n);
  // void remove_g(size_t n);
  size_t get_num_g();

  void get_A_matrix(SymEngine::DenseMatrix &result);
  void get_B_matrix(SymEngine::DenseMatrix &result);
  void get_C_matrix(SymEngine::DenseMatrix &result);
  void get_D_matrix(SymEngine::DenseMatrix &result);

  void accept(SystemVisitor &visitor);

protected:
  // Vector of symbolic state variables.
  SymEngine::vec_basic states_;

  // Vector of symbolic input variables.
  SymEngine::vec_basic inputs_;

  // Vector of state equations.
  SymEngine::vec_basic f_;

  // Vector of output equations.
  SymEngine::vec_basic g_;

  // TODO: Add sparse matrix backend to state space class.
  // SymEngine::CSRMatrix A;
  // SymEngine::CSRMatrix B;
  // SymEngine::CSRMatrix C;
  // SymEngine::CSRMatrix D;
};


bool check_abcd(SymEngine::MatrixBase &A,
                SymEngine::MatrixBase &B,
                SymEngine::MatrixBase &C,
                SymEngine::MatrixBase &D);

void set_abcd(StateSpace &obj,
              SymEngine::DenseMatrix &A,
              SymEngine::DenseMatrix &B,
              SymEngine::DenseMatrix &C,
              SymEngine::DenseMatrix &D);

// Separate dx/dt = f(.) + g(.)u into f(.) and g(.) terms.
void nonlinear_sep();

void c2d();
void d2c();

void similarity_transform(StateSpace &obj, SymEngine::DenseMatrix &P);

// ----------------------------------------------------------------------
// Linearization
//
void linearize(StateSpace &obj);
// void linearize(const SymEngine::vec_basic &eq);

} // Controls

#endif /* end of include guard: SYMCTRL_STATE_SPACE_HPP */
