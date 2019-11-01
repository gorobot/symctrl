#ifndef SYMCTRL_MATH_FUNCTOR_FUNCTOR_HPP
#define SYMCTRL_MATH_FUNCTOR_FUNCTOR_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BaseFunctor Class
//
template< typename R = void,  // Return type.
          typename ...Args >  // Functor args.
class BaseFunctor {
public:
  // Virtual functor evaluation function.
  virtual R eval(Args... args) = 0;
  virtual R operator()(Args... args) = 0;
};

// ----------------------------------------------------------------------
// Functor Class
//
template< typename DT,        // Derived type.
          typename R = void,  // Return type.
          typename ...Args>   // Functor args.
class Functor
    : public BaseFunctor<R, Args...> {
public:
  using BaseFunctor<R, Args...>::BaseFunctor;

  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }

  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }

  inline R eval(Args... args) {
    return this->operator~().eval(args...);
  }

  inline R operator()(Args... args) {
    return eval(args...);
  }
};

} // Math
} // Controls

#endif // SYMCTRL_MATH_FUNCTOR_FUNCTOR_HPP
