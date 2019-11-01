#ifndef SYMCTRL_TYPE_TRAITS_IS_SAFELY_CASTABLE_HPP
#define SYMCTRL_TYPE_TRAITS_IS_SAFELY_CASTABLE_HPP

#include <type_traits>

namespace Controls {

template <typename T, typename U, typename = void>
struct is_safely_castable : std::false_type {};

template <typename T, typename U>
struct is_safely_castable<T,
                          U,
                          void_t<decltype(static_cast<U>(std::declval<T>()))>
                          > : std::true_type
{};

} // Controls

#endif // SYMCTRL_TYPE_TRAITS_IS_SAFELY_CASTABLE_HPP
