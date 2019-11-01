#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_VAR_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_VAR_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/math/symbolic/sym_var/sym_var.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_var Expressions
//
// template<typename DT>
// inline sym_var &sym_var::operator+=(const Symbolic<DT> &rhs) {
//   // value_ += rhs.value();
//   // value_ = value_ + rhs.value();
//   // hash_ = hash_f<T>{}(value_);
//   return *this;
// }
//
// template<typename DT>
// inline sym_var &sym_var::operator-=(const Symbolic<DT> &rhs) {
//   // value_ -= rhs.value();
//   // value_ = value_ - rhs.value();
//   // hash_ = hash_f<T>{}(value_);
//   return *this;
// }
//
// template<typename DT>
// inline sym_var &sym_var::operator*=(const Symbolic<DT> &rhs) {
//   // value_ *= rhs.value();
//   // value_ = value_ * rhs.value();
//   // hash_ = hash_f<T>{}(value_);
//   return *this;
// }
//
// template<typename DT>
// inline sym_var &sym_var::operator/=(const Symbolic<DT> &rhs) {
//   // value_ /= rhs.value();
//   // value_ = value_ / rhs.value();
//   // hash_ = hash_f<T>{}(value_);
//   return *this;
// }

// template<typename DT>
// inline void sym_var::apply(const Symbolic<DT> &rhs) {
//   SYMCTRL_DEBUG("sym_var::apply");
//
// }

// template<typename DT>
// inline void sym_var::apply_sub(const Symbolic<DT> &rhs) {
//   SYMCTRL_DEBUG("sym_var::apply_sub");
//
// }
//
// template<typename DT>
// inline void sym_var::apply_mul(const Symbolic<DT> &rhs) {
//   SYMCTRL_DEBUG("sym_var::apply_mul");
//
// }
//
// template<typename DT>
// inline void sym_var::apply_div(const Symbolic<DT> &rhs) {
//   SYMCTRL_DEBUG("sym_var::apply_div");
//
// }
//
// template<typename DT>
// inline void sym_var::apply_diff(const Symbolic<DT> &rhs) {
//   SYMCTRL_DEBUG("sym_var::apply_diff");
//
// }

// ----------------------------------------------------------------------
// sym_var Equal
//
inline bool equal(const sym_var &lhs, const sym_var &rhs) {
  return lhs.hash() == rhs.hash();
}

template<typename DT>
inline bool equal(const sym_var &lhs, const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_var == Symbolic");
  return lhs.hash() == (~rhs).hash();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_VAR_HPP
