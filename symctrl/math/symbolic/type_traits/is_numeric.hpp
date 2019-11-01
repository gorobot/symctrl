#ifndef SYMCTRL_MATH_SYMBOLIC_TYPE_TRAITS_IS_NUMERIC_HPP
#define SYMCTRL_MATH_SYMBOLIC_TYPE_TRAITS_IS_NUMERIC_HPP

#include <utility>

#include <symctrl/math/symbolic/sym_number/sym_number.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_numeric_s_helper
//
template<class T>
struct is_numeric_s_helper {
private:
  template<typename DT>
  static std::true_type test(sym_number<DT> &);

  template<typename DT>
  static std::true_type test(const sym_number<DT> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_numeric_s_t
//
template<typename T>
using is_numeric_s_t = typename is_numeric_s_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_numeric_s
//
template<typename T>
struct is_numeric_s : is_numeric_s_t<T>::type {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_TYPE_TRAITS_IS_NUMERIC_HPP
