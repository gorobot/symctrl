#ifndef SYMCTRL_TRAITS_INTEGER_SEQUENCE_HPP
#define SYMCTRL_TRAITS_INTEGER_SEQUENCE_HPP

namespace Controls {

// ----------------------------------------------------------------------
// integer_sequence (C++11 Implementation)
//
template<int ...>
struct integer_sequence {};

// ----------------------------------------------------------------------
// make_integer_sequence
//
template<int N, int ...S>
struct make_integer_sequence : make_integer_sequence<N-1, N-1, S...> { };

template<int ...S>
struct make_integer_sequence<0, S...> {
  using type = integer_sequence<S...>;
};

} // Controls

#endif // SYMCTRL_TRAITS_INTEGER_SEQUENCE_HPP
