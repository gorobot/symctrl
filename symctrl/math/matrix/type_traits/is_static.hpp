#ifndef SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_STATIC_HPP
#define SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_STATIC_HPP

#include <type_traits>
#include <utility>

#include <symctrl/math/matrix/static/dense.hpp>
#include <symctrl/math/matrix/static/vector.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_static_helper
//
template<class T>
struct is_static_helper {
private:
  template<typename DT, size_t N, size_t M>
  static std::true_type test(StaticDense<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(const StaticDense<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(StaticVector<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(const StaticVector<DT, N, M> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_static_t
//
template<typename T>
using is_static_t = typename is_static_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_static
//
template<typename T>
struct is_static : is_static_t<T>::type {};

// ----------------------------------------------------------------------
// SFINAE enable_if_static
//
template<typename T, typename R = void>
struct enable_if_static : std::enable_if<is_static<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_static_t
//
template<typename T, typename R = void>
using enable_if_static_t = typename enable_if_static<T, R>::type;

// ----------------------------------------------------------------------
// SFINAE disable_if_static
//
template<typename T, typename R = void>
struct disable_if_static : std::enable_if<!is_static<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE disable_if_static_t
//
template<typename T, typename R = void>
using disable_if_static_t = typename disable_if_static<T, R>::type;

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_STATIC_HPP
