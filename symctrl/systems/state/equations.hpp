#ifndef SYMCTRL_SYSTEMS_EQUATIONS
#define SYMCTRL_SYSTEMS_EQUATIONS

#include <symctrl/math/matrix/vector.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// StateEquations
//
class StateEquations : public Math::SymbolicVector {
private:
  using result_type = StateEquations;

public:
  using Math::SymbolicVector::SymbolicVector;
  using Math::SymbolicVector::operator=;

  inline StateEquations &operator=(const StateEquations &rhs);
};

// ----------------------------------------------------------------------
// StateEquations Assignment Operator
//
inline StateEquations&
StateEquations::operator=(const StateEquations &rhs) {
  SymbolicVector::operator=(rhs);
  return *this;
}

} // Controls

#endif // SYMCTRL_SYSTEMS_EQUATIONS
