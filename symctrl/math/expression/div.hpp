#ifndef SYMCTRL_MATH_EXPRESSION_DIV_HPP
#define SYMCTRL_MATH_EXPRESSION_DIV_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprDiv
//
template< template<typename> class DT,  // Derived type.
          typename T1,                  // Lhs type.
          typename T2 >                 // Rhs type.
class ExprDiv
    : public Expression<DT<ExprDiv<DT, T1, T2>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_DIV_HPP
