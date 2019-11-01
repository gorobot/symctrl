#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_NUMBER_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_NUMBER_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/math/symbolic/sym_number/sym_number.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_numeric.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_number Expressions
//
//
// inline sym_number &sym_number::operator+=(const T &rhs) {
//   real_ += rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
//
// inline sym_number &sym_number::operator-=(const T &rhs) {
//   real_ -= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
//
// inline sym_number &sym_number::operator*=(const T &rhs) {
//   real_ *= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
//
// inline sym_number &sym_number::operator/=(const T &rhs) {
//   real_ /= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }

template<typename T>
template<typename DT>
inline void sym_number<T>::apply(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number::apply");
  SYMCTRL_STATIC_ASSERT((~rhs).canEvaluate(), "Cannot evaluate rhs.");
  real_ = (~rhs).real();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_add(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number::apply_add");
  SYMCTRL_STATIC_ASSERT((~rhs).canEvaluate(), "Cannot evaluate rhs.");
  real_ += (~rhs).real();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_diff(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number::apply_diff");
  SYMCTRL_STATIC_ASSERT((~rhs).canEvaluate(), "Cannot evaluate rhs.");
  real_ = 0;
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_div(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number::apply_div");
  SYMCTRL_STATIC_ASSERT((~rhs).canEvaluate(), "Cannot evaluate rhs.");
  real_ /= (~rhs).real();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_mul(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number::apply_mul");
  SYMCTRL_STATIC_ASSERT((~rhs).canEvaluate(), "Cannot evaluate rhs.");
  real_ *= (~rhs).real();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_neg(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number::apply_neg");
  SYMCTRL_STATIC_ASSERT((~rhs).canEvaluate(), "Cannot evaluate rhs.");
  real_ = -1*(~rhs).real();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_pow(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number::apply_pow");
  SYMCTRL_STATIC_ASSERT((~rhs).canEvaluate(), "Cannot evaluate rhs.");
  // real_ = (~rhs).real();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_sub(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number::apply_sub");
  SYMCTRL_STATIC_ASSERT((~rhs).canEvaluate(), "Cannot evaluate rhs.");
  real_ -= (~rhs).real();
  if(hash_) {
    hash_ = 0;
  }
}

// ----------------------------------------------------------------------
// sym_number Equal
//
template<typename T1, typename T2>
inline bool equal(const sym_number<T1> &lhs, const sym_number<T2> &rhs) {
  return lhs.real() == rhs.real();
}

template<typename T, typename DT>
inline bool equal(const sym_number<T> &lhs, const Symbolic<DT> &rhs) {
  return lhs.hash() == (~rhs).hash();
}

template<typename T1, typename T2>
inline auto operator==(const sym_number<T1> &lhs, const T2 &rhs)
-> enable_if_numeric_t<T2, bool> {
  return lhs.real() == rhs;
}

template<typename T1, typename T2>
inline auto operator!=(const sym_number<T1> &lhs, const T2 &rhs)
-> enable_if_numeric_t<T2, bool> {
  return lhs.real() != rhs;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_NUMBER_HPP
