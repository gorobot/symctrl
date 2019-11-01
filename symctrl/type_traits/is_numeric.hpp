#ifndef SYMCTRL_TYPE_TRAITS_IS_NUMERIC_HPP
#define SYMCTRL_TYPE_TRAITS_IS_NUMERIC_HPP

namespace Controls {

// ----------------------------------------------------------------------
// is_integer
//
template<typename T>
struct is_integer : std::integral_constant<bool,
  std::is_same<typename std::remove_cv<T>::type, short>::value ||
  std::is_same<typename std::remove_cv<T>::type, int>::value ||
  std::is_same<typename std::remove_cv<T>::type, long>::value ||
  std::is_same<typename std::remove_cv<T>::type, long long>::value >
{};

// ----------------------------------------------------------------------
// is_integer_t
//
template<typename T>
using is_integer_t = typename is_integer<T>::type;

// ----------------------------------------------------------------------
// SFINAE enable_if_integer
//
template<typename T, typename R = void>
struct enable_if_integer :
  std::enable_if<is_integer<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_integer_t
//
template<typename T, typename R = void>
using enable_if_integer_t =
  typename enable_if_integer<T, R>::type;

// ----------------------------------------------------------------------
// is_floating_point
//
template<typename T>
struct is_floating_point : std::integral_constant<bool,
  std::is_same<typename std::remove_cv<T>::type, float>::value ||
  std::is_same<typename std::remove_cv<T>::type, double>::value ||
  std::is_same<typename std::remove_cv<T>::type, long double>::value >
{};

// ----------------------------------------------------------------------
// is_floating_point_t
//
template<typename T>
using is_floating_point_t = typename is_floating_point<T>::type;

// ----------------------------------------------------------------------
// SFINAE enable_if_floating_point
//
template<typename T, typename R = void>
struct enable_if_floating_point :
  std::enable_if<is_floating_point<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_floating_point_t
//
template<typename T, typename R = void>
using enable_if_floating_point_t =
  typename enable_if_floating_point<T, R>::type;

// ----------------------------------------------------------------------
// is_numeric
//
template<typename T>
struct is_numeric : std::integral_constant<bool,
  is_integer_t<T>::value ||
  is_floating_point<T>::value >
{};

// ----------------------------------------------------------------------
// is_numeric_t
//
template<typename T>
using is_numeric_t = typename is_numeric<T>::type;

// ----------------------------------------------------------------------
// SFINAE enable_if_integer
//
template<typename T, typename R = void>
struct enable_if_numeric :
  std::enable_if<is_numeric<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_numeric_t
//
template<typename T, typename R = void>
using enable_if_numeric_t =
  typename enable_if_numeric<T, R>::type;


} // Controls

#endif // SYMCTRL_TYPE_TRAITS_IS_NUMERIC_HPP
