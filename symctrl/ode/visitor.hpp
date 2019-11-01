#ifndef SYMCTRL_ODE_VISITOR_HPP
#define SYMCTRL_ODE_VISITOR_HPP

#include <vector>

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/systems/visitor.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// ODE Visitor
//
class OdeVisitor : public SystemVisitor<OdeVisitor> {
protected:
  std::vector<double> initial_condition_;
  std::vector<double> &t_result_;
  std::vector<double> &x_result_;

  ode_options options_;

public:
  explicit inline OdeVisitor(const std::vector<double> initial_condition,
                             std::vector<double> &t_result,
                             std::vector<double> &x_result,
                             const ode_options opts);
};

// ----------------------------------------------------------------------
// OdeVisitor Constructor
//
inline OdeVisitor::OdeVisitor(const std::vector<double> initial_condition,
                              std::vector<double> &t_result,
                              std::vector<double> &x_result,
                              const ode_options opts) :
                              t_result_(t_result),
                              x_result_(x_result) {
  //
  initial_condition_ = initial_condition;
  options_ = opts;

  // +1 to handle rounding errors.
  size_t cap = ((opts.t_end() - opts.t_begin()) / opts.step_size()) + 1;

  t_result_.reserve(cap + 1);
  x_result_.reserve(t_result.capacity() * initial_condition.size());

  // t_result[0] = opts.t_begin();
  // for(size_t i = 1; i < opts.t_end(); i++) {
  //   t_result[i] = t_result[i - 1] + opts.step_size();
  // }
}


} // Controls

#endif // SYMCTRL_ODE_VISITOR_HPP
