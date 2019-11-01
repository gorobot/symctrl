#ifndef SYMCTRL_SHIMS_DEFAULT_HPP
#define SYMCTRL_SHIMS_DEFAULT_HPP

#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// default_value
//
template<typename T>
inline constexpr T default_value() {
  return T();
}

// template<>
// inline symbolic_t default_value() {
//   return symbolic_zero();
// }

// ----------------------------------------------------------------------
// default_one
//
template<typename T>
inline constexpr T default_one() {
  return T(1);
}

// template<>
// inline symbolic_t default_one() {
//   return symbolic_one();
// }

// ----------------------------------------------------------------------
// default_zero
//
template<typename T>
inline constexpr T default_zero() {
  return T(0);
}

// template<>
// inline symbolic_t default_zero() {
//   return symbolic_zero();
// }

} // Controls

#endif // SYMCTRL_SHIMS_DEFAULT_HPP
