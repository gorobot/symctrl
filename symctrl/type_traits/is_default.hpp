#ifndef SYMCTRL_TYPE_TRAITS_IS_DEFAULT_HPP
#define SYMCTRL_TYPE_TRAITS_IS_DEFAULT_HPP

#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// is_default
//
template<typename T>
inline bool is_default(const T v) {
  return v == T();
}

// template<>
// inline bool is_default(const symbolic_t v) {
//   return SymEngine::eq(*v, *symbolic_zero());
// }

} // Controls

#endif // SYMCTRL_TYPE_TRAITS_IS_DEFAULT_HPP
