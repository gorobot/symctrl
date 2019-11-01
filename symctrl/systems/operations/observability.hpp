#ifndef SYMCTRL_SYSTEMS_OPERATIONS_OBSERVABILITY_HPP
#define SYMCTRL_SYSTEMS_OPERATIONS_OBSERVABILITY_HPP

#include <symctrl/math/matrix/block.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/systems/statespace/statespace.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Observability Matrix
//
Math::BlockMatrix<symbolic_t>
observability_matrix(const Math::SymbolicDense &A,
                     const Math::SymbolicDense &C);

Math::BlockMatrix<symbolic_t> observability_matrix(const StateSpace &sys);

} // Controls

#endif // SYMCTRL_SYSTEMS_OPERATIONS_OBSERVABILITY_HPP
