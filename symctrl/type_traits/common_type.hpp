#ifndef SYMCTRL_TYPE_TRAITS_COMMON_TYPE_HPP
#define SYMCTRL_TYPE_TRAITS_COMMON_TYPE_HPP

#include <type_traits>

namespace Controls {

// ----------------------------------------------------------------------
// common_type
//
template<typename ...T>
using common_type = std::common_type<T...>;

// ----------------------------------------------------------------------
// common_type_t
//
template<typename ...T>
using common_type_t = typename common_type<T...>::type;

} // Controls

#endif // SYMCTRL_TYPE_TRAITS_COMMON_TYPE_HPP
