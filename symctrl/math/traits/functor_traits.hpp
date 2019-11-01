#ifndef SYMCTRL_TRAITS_FUNCTOR_TRAITS_HPP
#define SYMCTRL_TRAITS_FUNCTOR_TRAITS_HPP

#include <tuple>

namespace Controls {

// ----------------------------------------------------------------------
// functor_return
//
template<typename F>
struct functor_return : functor_return<decltype(&F::operator())> {
  using type = typename functor_return<decltype(&F::operator())>::type;
};

// Generic Functor
template<typename F, typename R, typename ...Args>
struct functor_return<R(F::*)(Args...) const> {
  using type = R;
};

// Lambda
template<typename R, typename ...Args>
struct functor_return<R(*)(Args...)> {
  using type = R;
};

// ----------------------------------------------------------------------
// functor_return_t
//
template<typename F>
using functor_return_t = typename functor_return<F>::type;

// ----------------------------------------------------------------------
// functor_args
//
template<typename F>
struct functor_args {
  using type = typename functor_args<decltype(&F::operator())>::type;
};

// Generic Functor
template<typename F, typename R, typename ...Args>
struct functor_args<R(F::*)(Args...) const> {
  using type = std::tuple<Args...>;
};

// Lambda
template<typename R, typename ...Args>
struct functor_args<R(*)(Args...)> {
  using type = std::tuple<Args...>;
};

// ----------------------------------------------------------------------
// functor_args_t
//
template<typename F>
using functor_args_t = typename functor_args<F>::type;

} // Controls

#endif // SYMCTRL_TRAITS_FUNCTOR_TRAITS_HPP
