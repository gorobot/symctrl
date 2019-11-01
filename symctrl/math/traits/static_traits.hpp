#ifndef SYMCTRL_TRAITS_STATIC_TRAITS_HPP
#define SYMCTRL_TRAITS_STATIC_TRAITS_HPP

namespace Controls {

// ----------------------------------------------------------------------
// static_traits
//
template<typename T>
struct static_traits;

template<template<typename, size_t, size_t> class DT,
  typename T, size_t N, size_t M >
struct static_traits<DT<T, N, M>> {
public:
  static constexpr size_t nrows = N;
  static constexpr size_t ncols = M;
  using type = T;
};

} // Controls

#endif // SYMCTRL_TRAITS_STATIC_TRAITS_HPP
