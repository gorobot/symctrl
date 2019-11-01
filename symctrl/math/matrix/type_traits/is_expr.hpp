#ifndef SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_EXPR_HPP
#define SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_EXPR_HPP

#include <utility>

#include <symctrl/math/expression.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_expr_m_helper
//
template<class T>
struct is_expr_m_helper {
private:
  template<typename ...DT>
  static std::true_type test(Expression<Matrix<DT...>> &);

  template<typename ...DT>
  static std::true_type test(const Expression<Matrix<DT...>> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_expr_m_t
//
template<class T>
using is_expr_m_t = typename is_expr_m_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_expr_m
//
template<typename T>
struct is_expr_m : is_expr_m_t<T>::type {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_EXPR_HPP
