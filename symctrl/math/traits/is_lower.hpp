#ifndef SYMCTRL_TRAITS_IS_LOWER_HPP
#define SYMCTRL_TRAITS_IS_LOWER_HPP

#include <tuple>
#include <type_traits>

#include <symctrl/traits/is_default_value.hpp>
#include <symctrl/traits/integer_sequence.hpp>
#include <symctrl/traits/static_traits.hpp>
#include <symctrl/math/matrix/static/dense.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// above_diagonal
//
constexpr bool above_diagonal(int row, int col) {
  return col > row;
}

// template <int, typename> struct selected;
//
// template <int T, typename ...Args>
// struct selected<T, integer_sequence<Args...>> {
//     using type = integer_sequence<T, Args...>;
// };
//
// template<int ...>
// struct filter;
//
// template<>
// struct filter<> {
//   using type = integer_sequence<>;
// };
//
// template<int T, int ...U>
// struct filter<T, U...> {
//   using type = typename std::conditional<
//     above_diagonal(T/3 + 1, T%3 + 1),
//     typename selected<T, filter<U...>::type>::type,
//     typename filter<U...>::type
//     >::type;
// };

// template<int, int...>
// struct selected;
//
// template<int C, int... D>
// struct selected<C, integer_sequence<D...>::type> {
//   using type = integer_sequence<C, D...>;
// }


template<size_t , int ...>
struct filter;

template<size_t M>
struct filter<M> {
  using type = integer_sequence<>;
};

template<size_t M, int C, int ...D>
struct filter<M, C, D...> {
  using type = typename std::conditional<
    above_diagonal(C/M + 1, C%M + 1),
    typename integer_sequence<C, filter<M, D...>::type>::type,
    typename filter<M, D...>::type
    >::type;
};


// ----------------------------------------------------------------------
// is_lower
//
template<typename T, T& C>
struct is_lower {
// private:
  using traits = static_traits<T>;

  SYMCTRL_STATIC_ASSERT(traits::ncols == traits::nrows,
    "StaticDense must have N = M");

  using sequence = make_integer_sequence<traits::nrows * traits::ncols>;

// public:
  // using filtered_seq = typename filter<traits::ncols, sequence>::type;
};

} // Controls

#endif // SYMCTRL_TRAITS_IS_LOWER_HPP
