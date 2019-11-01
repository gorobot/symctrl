#ifndef SYMCTRL_MATH_EXPRESSION_HPP
#define SYMCTRL_MATH_EXPRESSION_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Expression
//
template<typename DT>
class Expression : public DT {};

// ----------------------------------------------------------------------
// result_type_t
//
template<typename T>
using result_type_t = typename T::result_type;

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_HPP
