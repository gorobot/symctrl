#ifndef SYMCTRL_SHIMS_SYMBOLIC_HPP
#define SYMCTRL_SHIMS_SYMBOLIC_HPP

#include <type_traits>

// #include <symengine/add.h>
// #include <symengine/basic.h>
// #include <symengine/constants.h>
// #include <symengine/integer.h>
// #include <symengine/mul.h>
// #include <symengine/pow.h>
// #include <symengine/parser.h>
// #include <symengine/real_double.h>
// #include <symengine/symbol.h>

// #include <symctrl/math/random/random_variable.hpp>
#include <symctrl/type_traits/is_scalar.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// symbolic
//
struct symbolic {
  // using type = SymEngine::RCP<const SymEngine::Basic>;
};

// using symbolic_t = typename symbolic::type;

// ----------------------------------------------------------------------
// symbolic_integer
//
struct symbolic_integer {
  // using type = SymEngine::RCP<const SymEngine::Integer>;
};

// using symbolic_integer_t = typename symbolic_integer::type;

// ----------------------------------------------------------------------
// symbolic_variable
//
struct symbolic_variable {
  // using type = SymEngine::RCP<const SymEngine::Symbol>;
};

// using symbolic_symbol_t = typename symbolic_variable::type;

// ----------------------------------------------------------------------
// symbolic_rv
//
struct symbolic_rv {
  // using type = SymEngine::RCP<const Controls::Math::RandomVariable>;
};

// using symbolic_rv_t = typename symbolic_rv::type;

// ----------------------------------------------------------------------
// symbolic_one
//
// inline symbolic_t symbolic_one() {
  // return SymEngine::one;
// }

// ----------------------------------------------------------------------
// symbolic_zero
//
// inline symbolic_t symbolic_zero() {
  // return SymEngine::zero;
// }

} // Controls

#endif // SYMCTRL_SHIMS_SYMBOLIC_HPP
