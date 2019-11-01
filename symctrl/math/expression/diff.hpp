#ifndef SYMCTRL_MATH_EXPRESSION_DIFF_HPP
#define SYMCTRL_MATH_EXPRESSION_DIFF_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprDiff
//
template< template<typename> class DT,  // Derived type.
          typename T >                  // Operand type.
class ExprDiff
    : public Expression<DT<ExprDiff<DT, T>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_DIFF_HPP
