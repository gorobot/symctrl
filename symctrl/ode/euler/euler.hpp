#ifndef SYMCTRL_ODE_EULER_EULER_HPP
#define SYMCTRL_ODE_EULER_EULER_HPP

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/ode/visitor.hpp>
#include <symctrl/ode/options/options.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// EulerVisitor
//
class EulerVisitor : public OdeVisitor {
public:
  using OdeVisitor::OdeVisitor;

  void visit(StateSpace &sys);

  template<typename DT>
  void visit(System<DT> &sys) {}
};

// ----------------------------------------------------------------------
// ode_euler
//
void ode_euler(StateSpace &sys,
               std::vector<double> x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result);
//
void ode_euler(StateSpace &sys,
               std::vector<double> x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result,
               ode_options options);

} // Controls

#endif // SYMCTRL_ODE_EULER_EULER_HPP
