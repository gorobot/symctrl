#ifndef SYMCTRL_MATH_FUNCTOR_LAMBDA_HPP
#define SYMCTRL_MATH_FUNCTOR_LAMBDA_HPP

#include <functional>

#include <symctrl/math/functor/functor.hpp>
#include <symctrl/math/traits/functor_traits.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// LambdaFunctor
//
template< typename F,        // Function type.
          typename R,        // Return type.
          typename ...Args > // Function args.
class LambdaFunctor
    : public Functor<LambdaFunctor<F, R, Args...>, R, Args...> {
private:
  std::function<R(Args...)> f_;

public:
  explicit inline LambdaFunctor(F f) : f_(f) {};

  R eval(Args... args) {
    return f_(args...);
  }
};

// ----------------------------------------------------------------------
// Utility Functions
//
template< typename F,      // Functor type.
          typename R,      // Return type.
          typename >       // Empty typename.
struct lambda_shim;

template< typename F,      // Functor type.
          typename R,      // Return type.
          typename ...T >  // Tuple args.
struct lambda_shim<F, R, std::tuple<T...>> {
  using type = LambdaFunctor<F, R, T...>;
};

template<typename F>
inline auto lambda_functor(F&& f)
-> typename lambda_shim<F, functor_return_t<F>, functor_args_t<F>>::type {
  using ReturnType =
    typename lambda_shim<F, functor_return_t<F>, functor_args_t<F>>::type;
  return ReturnType(f);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_FUNCTOR_LAMBDA_HPP
