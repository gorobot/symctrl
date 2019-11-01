#ifndef SYMCTRL_MATH_EXPRESSION_MUL_HPP
#define SYMCTRL_MATH_EXPRESSION_MUL_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprMul
//
template< template<typename> class DT,  // Derived type.
          typename T1,                  // Lhs type.
          typename T2 >                 // Rhs type.
class ExprMul
    : public Expression<DT<ExprMul<DT, T1, T2>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_MUL_HPP
