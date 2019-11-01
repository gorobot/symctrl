#ifndef SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_MATRIX_HPP
#define SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_MATRIX_HPP

#include <type_traits>
#include <utility>

#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_matrix_helper
//
template<class T>
struct is_matrix_helper {
private:
  template<typename ...DT>
  static std::true_type test(Matrix<DT...> &);

  template<typename ...DT>
  static std::true_type test(const Matrix<DT...> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_matrix_t
//
template<typename T>
using is_matrix_t = typename is_matrix_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_matrix
//
template<typename T>
struct is_matrix : is_matrix_t<T>::type {};

// ----------------------------------------------------------------------
// SFINAE enable_if_matrix
//
template<typename T, typename R = void>
struct enable_if_matrix : std::enable_if<is_matrix<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_matrix_t
//
template<typename T, typename R = void>
using enable_if_matrix_t = typename enable_if_matrix<T, R>::type;

// ----------------------------------------------------------------------
// SFINAE disable_if_matrix
//
template<typename T, typename R = void>
struct disable_if_matrix : std::enable_if<!is_matrix<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE disable_if_matrix_t
//
template<typename T, typename R = void>
using disable_if_matrix_t = typename disable_if_matrix<T, R>::type;

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_MATRIX_HPP
