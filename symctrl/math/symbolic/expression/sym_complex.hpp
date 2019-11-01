#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_COMPLEX_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_COMPLEX_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/math/symbolic/sym_number/sym_complex.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_numeric.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_complex Expressions
//
// template<typename T>
// inline sym_complex<T> &sym_complex<T>::operator+=(const T &rhs) {
//   real_ += rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
// template<typename T>
// inline sym_complex<T> &sym_complex<T>::operator-=(const T &rhs) {
//   real_ -= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
// template<typename T>
// inline sym_complex<T> &sym_complex<T>::operator*=(const T &rhs) {
//   real_ *= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
// template<typename T>
// inline sym_complex<T> &sym_complex<T>::operator/=(const T &rhs) {
//   real_ /= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }

template<typename T>
template<typename DT>
inline void sym_complex<T>::apply(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex<T>::apply");
  real_ = (~rhs).real();
  imag_ = (~rhs).imag();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_complex<T>::apply_add(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex<T>::apply_add");
  real_ += (~rhs).real();
  imag_ += (~rhs).imag();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_complex<T>::apply_diff(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex<T>::apply_diff");
  real_ = T(0);
  imag_ = T(0);
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_complex<T>::apply_div(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex<T>::apply_div");
  real_ /= (~rhs).real();
  imag_ /= (~rhs).imag();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_complex<T>::apply_mul(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex<T>::apply_mul");
  real_ *= (~rhs).real();
  imag_ *= (~rhs).imag();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_complex<T>::apply_neg(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex<T>::apply_neg");
  real_ = -1*(~rhs).real();
  imag_ = -1*(~rhs).imag();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_complex<T>::apply_pow(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex<T>::apply_pow");
  // real_ = (~rhs).real();
  // imag_ = (~rhs).imag();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_complex<T>::apply_sub(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex<T>::apply_sub");
  real_ -= (~rhs).real();
  imag_ -= (~rhs).imag();
  if(hash_) {
    hash_ = 0;
  }
}

// ----------------------------------------------------------------------
// sym_complex Equal
//
template<typename T>
inline bool equal(const sym_complex<T> &lhs, const sym_complex<T> &rhs) {
  std::cout << "sym_complex == sym_complex" << '\n';
  return (lhs.real() == rhs.real() &&
          lhs.imag() == rhs.imag());
}

template<typename T, typename DT>
inline bool equal(const sym_complex<T> &lhs, const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_complex == Symbolic");
  return lhs.hash() == (~rhs).hash();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_COMPLEX_HPP
