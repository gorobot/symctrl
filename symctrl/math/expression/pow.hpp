#ifndef SYMCTRL_MATH_EXPRESSION_POW_HPP
#define SYMCTRL_MATH_EXPRESSION_POW_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprPow
//
template< template<typename> class DT,  // Derived type.
          typename T1,                  // Base type.
          typename T2 >                 // Exponent type.
class ExprPow
    : public Expression<DT<ExprPow<DT, T1, T2>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_POW_HPP
