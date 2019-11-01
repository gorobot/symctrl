#ifndef SYMCTRL_SYSTEMS_STATESPACE_STATESPACE_HPP
#define SYMCTRL_SYSTEMS_STATESPACE_STATESPACE_HPP

#include <algorithm>
#include <initializer_list>
#include <vector>

#include <symctrl/systems/system.hpp>
#include <symctrl/math/matrix/expression/matrix.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/vector.hpp>
#include <symctrl/math/matrix/operations/jacobian.hpp>
#include <symctrl/shims/symbolic.hpp>
#include <symctrl/type_traits/is_symbolic.hpp>

namespace Controls {

// class BaseController;
//
// template<typename CT>
// class Controller : public BaseController;

// ----------------------------------------------------------------------
// StateSpace
//
class StateSpace : public System<StateSpace> {
public:
  explicit inline StateSpace();

  explicit inline StateSpace(std::initializer_list<symbolic_t> x,
                             std::initializer_list<symbolic_t> u,
                             std::initializer_list<symbolic_t> f,
                             std::initializer_list<symbolic_t> g);
  explicit inline StateSpace(const std::vector<symbolic_t> &x,
                             const std::vector<symbolic_t> &u,
                             const std::vector<symbolic_t> &f,
                             const std::vector<symbolic_t> &g);
  explicit inline StateSpace(const Math::SymbolicVector &x,
                             const Math::SymbolicVector &u,
                             const Math::SymbolicVector &f,
                             const Math::SymbolicVector &g);
  explicit inline StateSpace(const Math::SymbolicDense &A,
                             const Math::SymbolicDense &B,
                             const Math::SymbolicDense &C,
                             const Math::SymbolicDense &D);

  inline StateSpace(const StateSpace &m);

  inline StateSpace &operator=(const StateSpace &rhs);

  template<typename DT>
  inline StateSpace &operator=(const Math::Matrix<DT> &rhs);

  template<typename T>
  inline auto operator+=(const T &rhs)
  -> enable_if_symbolic_t<T, StateSpace&>;
  template<typename T>
  inline auto operator-=(const T &rhs)
  -> enable_if_symbolic_t<T, StateSpace&>;
  template<typename T>
  inline auto operator*=(const T &rhs)
  -> enable_if_symbolic_t<T, StateSpace&>;
  template<typename T>
  inline auto operator/=(const T &rhs)
  -> enable_if_symbolic_t<T, StateSpace&>;

private:
  // Using a private nested class allows implementation details to be
  // abstracted from the public member variables.
  class ExpressionVector : public Math::SymbolicVector {
  public:
    using Math::SymbolicVector::SymbolicVector;
    using Math::SymbolicVector::operator=;
  };

public:
  // Vector of symbolic state variables.
  ExpressionVector state_variables;

  // Vector of symbolic input variables.
  ExpressionVector input_variables;

  // Vector of state equations.
  ExpressionVector state_equations;

  // Vector of output equations.
  ExpressionVector output_equations;

public:
  // System matrices.
  inline Math::SymbolicDense A() const;
  inline Math::SymbolicDense B() const;
  inline Math::SymbolicDense C() const;
  inline Math::SymbolicDense D() const;

  // template<typename CT>
  // inline void apply_(Controller<CT> &controller);

  inline void accept(Visitor &visitor);
};

// ----------------------------------------------------------------------
// StateSpace Constructor
//
inline StateSpace::StateSpace() {
  //
  state_variables = ExpressionVector(0);
  input_variables = ExpressionVector(0);
  state_equations = ExpressionVector(0);
  output_equations = ExpressionVector(0);
}

inline StateSpace::StateSpace(std::initializer_list<symbolic_t> x,
                              std::initializer_list<symbolic_t> u,
                              std::initializer_list<symbolic_t> f,
                              std::initializer_list<symbolic_t> g) {
  //
  state_variables = x;
  input_variables = u;
  state_equations = f;
  output_equations = g;
}

inline StateSpace::StateSpace(const std::vector<symbolic_t> &x,
                              const std::vector<symbolic_t> &u,
                              const std::vector<symbolic_t> &f,
                              const std::vector<symbolic_t> &g) :
                              state_variables(x),
                              input_variables(u),
                              state_equations(f),
                              output_equations(g) {
  //
  SYMCTRL_ASSERT(state_variables.size() == state_equations.size());
}

inline StateSpace::StateSpace(const Math::SymbolicVector &x,
                              const Math::SymbolicVector &u,
                              const Math::SymbolicVector &f,
                              const Math::SymbolicVector &g) :
                              state_variables(x),
                              input_variables(u),
                              state_equations(f),
                              output_equations(g) {
  //
  SYMCTRL_ASSERT(state_variables.size() == state_equations.size());
}

// inline StateSpace(const Math::SymbolicDense &A,
//                   const Math::SymbolicDense &B,
//                   const Math::SymbolicDense &C,
//                   const Math::SymbolicDense &D) {
//   //
// }

inline StateSpace::StateSpace(const StateSpace &m) {
  //
  state_variables = m.state_variables;
  input_variables = m.input_variables;
  state_equations = m.state_equations;
  output_equations = m.output_equations;
}

// ----------------------------------------------------------------------
// StateSpace Assignment Operator
//
inline StateSpace &StateSpace::operator=(const StateSpace &rhs) {
  state_variables = rhs.state_variables;
  input_variables = rhs.input_variables;
  state_equations = rhs.state_equations;
  output_equations = rhs.output_equations;

  return *this;
}

template<typename DT>
inline StateSpace &StateSpace::operator=(const Math::Matrix<DT> &rhs) {
  apply_(state_equations, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// StateSpace Member Function Definitions
//
inline Math::SymbolicDense StateSpace::A() const {
  return Math::jacobian(state_equations, state_variables);
}

inline Math::SymbolicDense StateSpace::B() const {
  return Math::jacobian(state_equations, input_variables);
}

inline Math::SymbolicDense StateSpace::C() const {
  return Math::jacobian(output_equations, state_variables);
}

inline Math::SymbolicDense StateSpace::D() const {
  return Math::jacobian(output_equations, input_variables);
}

// ----------------------------------------------------------------------
// State Matrix
//
inline Math::SymbolicDense state_matrix(const StateSpace &sys) {
  return sys.A();
}

// ----------------------------------------------------------------------
// Input Matrix
//
inline Math::SymbolicDense input_matrix(const StateSpace &sys) {
  return sys.B();
}

// ----------------------------------------------------------------------
// Output Matrix
//
inline Math::SymbolicDense output_matrix(const StateSpace &sys) {
  return sys.C();
}

// ----------------------------------------------------------------------
// Feed-forward Matrix
//
inline Math::SymbolicDense feedforward_matrix(const StateSpace &sys) {
  return sys.D();
}

const auto A_matrix = state_matrix;
const auto B_matrix = input_matrix;
const auto C_matrix = output_matrix;
const auto D_matrix = feedforward_matrix;

const auto system_matrix = state_matrix;
const auto feedthrough_matrix = feedforward_matrix;

} // Controls

#endif // SYMCTRL_SYSTEMS_STATESPACE_STATESPACE_HPP
