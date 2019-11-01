#ifndef SYMCTRL_MATH_TRAITS_HAS_RANDOM_VARIABLE_HPP
#define SYMCTRL_MATH_TRAITS_HAS_RANDOM_VARIABLE_HPP

#include <symengine/basic.h>

#include <symctrl/math/random/random_variable.hpp>
#include <symctrl/math/traits/is_random_variable.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// has_random_variable
//
inline bool has_random_variable(const symbolic_t &m) {
  std::vector<symbolic_t> args = m->get_args();

  if(args.empty()) {
    return false;
  }

  for(auto it = args.begin(); it != args.end(); ++it) {
    if(Math::is_random_variable(**it)) {
      return true;
    }
  }

  return false;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_TRAITS_HAS_RANDOM_VARIABLE_HPP
