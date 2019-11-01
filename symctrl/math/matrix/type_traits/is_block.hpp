#ifndef SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_BLOCK_HPP
#define SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_BLOCK_HPP

#include <utility>

#include <symctrl/math/matrix/block/block.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_block_helper
//
template<class T>
struct is_block_helper {
private:
  template<typename DT, template<typename> class MT>
  static std::true_type test(BlockMatrix<DT, MT> &);

  template<typename DT, template<typename> class MT>
  static std::true_type test(const BlockMatrix<DT, MT> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_block_t
//
template<typename T>
using is_block_t = typename is_block_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_block
//
template<typename T>
struct is_block : is_block_t<T>::type {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_BLOCK_HPP
