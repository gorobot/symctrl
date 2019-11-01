#ifndef SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_CONSTANT_HPP
#define SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_CONSTANT_HPP

#include <utility>

#include <symctrl/math/matrix/constant/constant.hpp>
#include <symctrl/math/matrix/constant/identity.hpp>
#include <symctrl/math/matrix/constant/ones.hpp>
#include <symctrl/math/matrix/constant/zeros.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_constant_helper
//
template<class T>
struct is_constant_helper {
private:
  template<typename DT, size_t N, size_t M, DT v_>
  static std::true_type test(ConstantMatrix<DT, N, M, v_> &);

  template<typename DT, size_t N, size_t M, DT v_>
  static std::true_type test(const ConstantMatrix<DT, N, M, v_> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(Identity<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(const Identity<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(Ones<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(const Ones<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(Zeros<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(const Zeros<DT, N, M> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_constant_t
//
template<typename T>
using is_constant_t = typename is_constant_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_constant
//
template<typename T>
struct is_constant : is_constant_t<T>::type {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_CONSTANT_HPP
