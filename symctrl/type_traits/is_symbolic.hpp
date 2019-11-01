#ifndef SYMCTRL_TRAITS_IS_SYMBOLIC_HPP
#define SYMCTRL_TRAITS_IS_SYMBOLIC_HPP

#include <type_traits>

#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// is_symbolic_integer
//
template<typename T>
using is_symbolic_integer = typename
  std::is_same<typename std::remove_cv<T>::type, symbolic_integer_t>::type;

// ----------------------------------------------------------------------
// is_symbolic_symbol
//
template<typename T>
using is_symbolic_symbol = typename
  std::is_same<typename std::remove_cv<T>::type, symbolic_symbol_t>::type;

// ----------------------------------------------------------------------
// is_symbolic_rv
//
template<typename T>
using is_symbolic_rv = typename
  std::is_same<typename std::remove_cv<T>::type, symbolic_rv_t>::type;

// ----------------------------------------------------------------------
// is_symbolic
//
template<typename T>
struct is_symbolic : std::integral_constant<bool,
  std::is_same<typename std::remove_cv<T>::type, symbolic_t>::value ||
  is_symbolic_integer<T>::value ||
  is_symbolic_symbol<T>::value ||
  is_symbolic_rv<T>::value >
{};

// ----------------------------------------------------------------------
// is_symbolic_t
//
template<typename T>
using is_symbolic_t = typename is_symbolic<T>::type;

// ----------------------------------------------------------------------
// SFINAE enable_if_symbolic
//
template<typename T, typename R = void>
struct enable_if_symbolic :
  std::enable_if<is_symbolic<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_symbolic_t
//
template<typename T, typename R = void>
using enable_if_symbolic_t =
  typename enable_if_symbolic<T, R>::type;

} // Controls

#endif // SYMCTRL_TRAITS_IS_SYMBOLIC_HPP
