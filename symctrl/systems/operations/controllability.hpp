#ifndef SYMCTRL_SYSTEMS_OPERATIONS_CONTROLLABILITY_HPP
#define SYMCTRL_SYSTEMS_OPERATIONS_CONTROLLABILITY_HPP

#include <symctrl/math/matrix/block.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/systems/statespace/statespace.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Controllability Matrix
//
Math::BlockMatrix<symbolic_t>
controllability_matrix(const Math::SymbolicDense &A,
                       const Math::SymbolicDense &B);

Math::BlockMatrix<symbolic_t> controllability_matrix(const StateSpace &sys);

} // Controls

#endif // SYMCTRL_SYSTEMS_OPERATIONS_CONTROLLABILITY_HPP
