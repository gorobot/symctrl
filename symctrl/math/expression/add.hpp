#ifndef SYMCTRL_MATH_EXPRESSION_ADD_HPP
#define SYMCTRL_MATH_EXPRESSION_ADD_HPP

#include <symctrl/math/expression.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprAdd
//
template< template<typename> class DT,  // Derived type.
          typename T1,                  // Lhs type.
          typename T2 >                 // Rhs type.
class ExprAdd
    : public Expression<DT<ExprAdd<DT, T1, T2>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_ADD_HPP
