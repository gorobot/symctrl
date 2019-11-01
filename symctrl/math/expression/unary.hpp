#ifndef SYMCTRL_MATH_EXPRESSION_UNARY_HPP
#define SYMCTRL_MATH_EXPRESSION_UNARY_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprUnary
//
template< template<typename> class DT,  // Derived type.
          typename T >                  // Operand type.
class ExprUnary
    : public Expression<DT<ExprUnary<DT, T>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_UNARY_HPP
