#ifndef SYMCTRL_MATH_TRAITS_IS_RANDOM_VARIABLE_HPP
#define SYMCTRL_MATH_TRAITS_IS_RANDOM_VARIABLE_HPP

#include <symengine/basic.h>

#include <symctrl/math/random/random_variable.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// is_random_variable
//
inline bool is_random_variable(const SymEngine::Basic &b) {
    return dynamic_cast<const RandomVariable*>(&b) != nullptr;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_TRAITS_IS_RANDOM_VARIABLE_HPP
