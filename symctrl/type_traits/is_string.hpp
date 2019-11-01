#ifndef SYMCTRL_TYPE_TRAITS_IS_STRING_HPP
#define SYMCTRL_TYPE_TRAITS_IS_STRING_HPP

#include <string>

namespace Controls {

// ----------------------------------------------------------------------
// is_cstr
//
template<typename T>
struct is_cstr : std::integral_constant<bool,
  std::is_same<typename std::remove_cv<T>::type, char>::value ||
  std::is_same<typename std::remove_cv<T>::type, char*>::value ||
  std::is_same<typename std::remove_cv<T>::type, const char*>::value ||
  std::is_same<typename std::remove_cv<T>::type, char[]>::value ||
  std::is_same<typename std::remove_cv<T>::type, const char[]>::value >
{};

// ----------------------------------------------------------------------
// is_cstr_t
//
template<typename T>
using is_cstr_t = typename is_cstr<T>::type;

// ----------------------------------------------------------------------
// SFINAE enable_if_cstr
//
template<typename T, typename R = void>
struct enable_if_cstr :
  std::enable_if<is_cstr<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_cstr_t
//
template<typename T, typename R = void>
using enable_if_cstr_t =
  typename enable_if_cstr<T, R>::type;

// ----------------------------------------------------------------------
// is_stdstring
//
template<typename T>
struct is_stdstring : std::integral_constant<bool,
  std::is_same<typename std::remove_cv<T>::type, std::string>::value >
{};

// ----------------------------------------------------------------------
// is_stdstring_t
//
template<typename T>
using is_stdstring_t = typename is_stdstring<T>::type;

// ----------------------------------------------------------------------
// SFINAE enable_if_string
//
template<typename T, typename R = void>
struct enable_if_stdstring :
  std::enable_if<is_stdstring<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_stdstring_t
//
template<typename T, typename R = void>
using enable_if_stdstring_t =
  typename enable_if_stdstring<T, R>::type;

// ----------------------------------------------------------------------
// is_string
//
template<typename T>
struct is_string : std::integral_constant<bool,
  is_cstr<T>::value ||
  is_stdstring<T>::value >
{};

// ----------------------------------------------------------------------
// is_string_t
//
template<typename T>
using is_string_t = typename is_string<T>::type;

// ----------------------------------------------------------------------
// SFINAE enable_if_string
//
template<typename T, typename R = void>
struct enable_if_string :
  std::enable_if<is_string<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_string_t
//
template<typename T, typename R = void>
using enable_if_string_t =
  typename enable_if_string<T, R>::type;


} // Controls

#endif // SYMCTRL_TYPE_TRAITS_IS_STRING_HPP
