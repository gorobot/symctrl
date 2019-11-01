#ifndef SYMCTRL_MATH_SYMBOLIC_TYPE_TRAITS_IS_EXPR_HPP
#define SYMCTRL_MATH_SYMBOLIC_TYPE_TRAITS_IS_EXPR_HPP

#include <utility>

#include <symctrl/math/expression.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_expr_s_helper
//
template<class T>
struct is_expr_s_helper {
private:
  template<typename ...DT>
  static std::true_type test(Expression<Symbolic<DT...>> &);

  template<typename ...DT>
  static std::true_type test(const Expression<Symbolic<DT...>> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_expr_s_t
//
template<class T>
using is_expr_s_t = typename is_expr_s_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_expr_s
//
template<typename T>
struct is_expr_s : is_expr_s_t<T>::type {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_TYPE_TRAITS_IS_EXPR_HPP
