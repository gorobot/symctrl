#ifndef SYMCTRL_MATH_EXPRESSION_INVERSE_HPP
#define SYMCTRL_MATH_EXPRESSION_INVERSE_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprInverse
//
template< template<typename> class DT,  // Derived type.
          typename T >                  // Operand type.
class ExprInverse
    : public Expression<DT<ExprInverse<DT, T>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_INVERSE_HPP
