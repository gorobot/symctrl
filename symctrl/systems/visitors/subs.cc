#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/subs.h>

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/statespace.hpp>
#include <symctrl/systems/transferfunction.hpp>
#include <symctrl/systems/visitor.hpp>
#include <symctrl/systems/visitors/subs.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// SubsVisitor StateSpace
//
void SubsVisitor::visit(StateSpace &sys) {
  SymEngine::map_basic_basic d;
  d[key_] = map_;

  for(size_t i = 0; i < sys.state_variables.size(); i++) {
    sys.state_variables[i] = SymEngine::ssubs(sys.state_variables[i], d);
  }

  for(size_t i = 0; i < sys.input_variables.size(); i++) {
    sys.input_variables[i] = SymEngine::ssubs(sys.input_variables[i], d);
  }

  for(size_t i = 0; i < sys.state_equations.size(); i++) {
    sys.state_equations[i] = SymEngine::ssubs(sys.state_equations[i], d);
  }

  for(size_t i = 0; i < sys.output_equations.size(); i++) {
    sys.output_equations[i] = SymEngine::ssubs(sys.output_equations[i], d);
  }
}

// ----------------------------------------------------------------------
// SubsVisitor TransferFunction
//
void SubsVisitor::visit(TransferFunction &sys) {
  SymEngine::map_basic_basic d;
  d[key_] = map_;

  sys.numerator() = SymEngine::ssubs(sys.numerator(), d);

  sys.denominator() = SymEngine::ssubs(sys.denominator(), d);
}

} // Controls
