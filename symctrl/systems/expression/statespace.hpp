#ifndef SYMCTRL_SYSTEMS_EXPRESSION_STATESPACE_HPP
#define SYMCTRL_SYSTEMS_EXPRESSION_STATESPACE_HPP

#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/expression/vector.hpp>
#include <symctrl/math/matrix/expression/matrix.hpp>
#include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/type_traits/is_scalar.hpp>
#include <symctrl/type_traits/is_symbolic.hpp>
#include <symctrl/shims/equal.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// StateSpace Expressions
//
template<typename T>
inline auto StateSpace::operator+=(const T &rhs)
-> enable_if_symbolic_t<T, StateSpace&> {
  state_equations += rhs;

  return *this;
}

template<typename T>
inline auto StateSpace::operator-=(const T &rhs)
-> enable_if_symbolic_t<T, StateSpace&> {
  state_equations -= rhs;

  return *this;
}

template<typename T>
inline auto StateSpace::operator*=(const T &rhs)
-> enable_if_symbolic_t<T, StateSpace&> {
  state_equations *= rhs;

  return *this;
}

template<typename T>
inline auto StateSpace::operator/=(const T &rhs)
-> enable_if_symbolic_t<T, StateSpace&> {
  state_equations /= rhs;

  return *this;
}

// ----------------------------------------------------------------------
// StateSpace Add Operator
//
template<typename M1>
inline const Math::ExprAdd<M1, Math::SymbolicVector>
operator+(const Math::Matrix<M1> &lhs, const StateSpace &rhs) {
  return Math::ExprAdd<M1, Math::SymbolicVector>(~lhs, ~rhs.state_equations);
}

template<typename M2>
inline const Math::ExprAdd<Math::SymbolicVector, M2>
operator+(const StateSpace &lhs, const Math::Matrix<M2> &rhs) {
  return Math::ExprAdd<Math::SymbolicVector, M2>(~lhs.state_equations, ~rhs);
}

template<typename T>
inline auto
operator+(const T &lhs, const StateSpace &rhs)
-> enable_if_symbolic_t<T, const Math::ExprUnary<Math::SymbolicVector>> {
  Math::SymbolicVector tmp(rhs.state_equations);
  return Math::ExprUnary<Math::SymbolicVector>(tmp += lhs);
}

template<typename T>
inline auto
operator+(const StateSpace &lhs, const T &rhs)
-> enable_if_symbolic_t<T, const Math::ExprUnary<Math::SymbolicVector>> {
  Math::SymbolicVector tmp(lhs.state_equations);
  return Math::ExprUnary<Math::SymbolicVector>(tmp += rhs);
}

// ----------------------------------------------------------------------
// StateSpace Mul Operator
//
template<typename M1>
inline const Math::ExprMul<M1, Math::SymbolicVector>
operator*(const Math::Matrix<M1> &lhs, const StateSpace &rhs) {
  return Math::ExprMul<M1, Math::SymbolicVector>(~lhs, ~rhs.state_equations);
}

template<typename M2>
inline const Math::ExprMul<Math::SymbolicVector, M2>
operator*(const StateSpace &lhs, const Math::Matrix<M2> &rhs) {
  return Math::ExprMul<Math::SymbolicVector, M2>(~lhs.state_equations, ~rhs);
}

template<typename T>
inline auto
operator*(const T &lhs, const StateSpace &rhs)
-> enable_if_symbolic_t<T, const Math::ExprUnary<Math::SymbolicVector>> {
  Math::SymbolicVector tmp(rhs.state_equations);
  return Math::ExprUnary<Math::SymbolicVector>(tmp *= lhs);
}

template<typename T>
inline auto
operator*(const StateSpace &lhs, const T &rhs)
-> enable_if_symbolic_t<T, const Math::ExprUnary<Math::SymbolicVector>> {
  Math::SymbolicVector tmp(lhs.state_equations);
  return Math::ExprUnary<Math::SymbolicVector>(tmp *= rhs);
}

// ----------------------------------------------------------------------
// StateSpace equal
//
inline bool equal(const StateSpace &lhs, const StateSpace &rhs) {
  if(lhs.state_variables.size() != rhs.state_variables.size()) {
    return false;
  }

  if(!equal(lhs.state_variables, rhs.state_variables)) {
    return false;
  }

  if(lhs.input_variables.size() != rhs.input_variables.size()) {
    return false;
  }

  if(!equal(lhs.input_variables, rhs.input_variables)) {
    return false;
  }

  if(lhs.state_equations.size() != rhs.state_equations.size()) {
    return false;
  }

  if(!equal(lhs.state_equations, rhs.state_equations)) {
    return false;
  }

  if(lhs.output_equations.size() != rhs.output_equations.size()) {
    return false;
  }

  if(!equal(lhs.output_equations, rhs.output_equations)) {
    return false;
  }

  return true;
}

} // Controls

#endif // SYMCTRL_SYSTEMS_EXPRESSION_STATESPACE_HPP
