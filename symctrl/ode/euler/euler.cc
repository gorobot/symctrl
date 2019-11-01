#include <tuple>
#include <vector>

// #include <symengine/basic.h>
// #include <symengine/dict.h>
#include <symengine/lambda_double.h>
#include <symengine/symbol.h>
#include <symengine/visitor.h>

#include <symctrl/math/random.hpp>
#include <symctrl/ode/ode.hpp>
#include <symctrl/ode/euler/euler.hpp>
#include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/shims/symbolic.hpp>

using SymEngine::symbol;
using SymEngine::LambdaRealDoubleVisitor;

namespace Controls {

// ----------------------------------------------------------------------
// EulerVisitor (StateSpace)
//
void EulerVisitor::visit(StateSpace &sys) {
  size_t n_ = sys.state_equations.size();

  std::vector<LambdaRealDoubleVisitor> v(n_);

  // Create a list of "parameters" that will be passed to dx/dt = f(...)
  std::vector<symbolic_t> params = sys.state_variables.as_vec();

  // Make sure t is one of the function parameters.
  symbolic_symbol_t t = symbol("t");
  auto it = params.begin();
  params.insert(it, t);

  //
  std::vector<symbolic_t> equations = sys.state_equations.as_vec();

  // Initialize the RNG.
  std::random_device gen;

  std::vector<symbolic_t> args;
  std::vector<symbolic_t> rv_vec;

  // Find all random variables in the state equations.
  for(size_t i = 0; i < n_; i++) {
    args = sys.state_equations[i]->get_args();

    if(!args.empty()) {
      for(auto it = args.begin(); it != args.end(); ++it) {
        if(Math::is_random_variable(**it)) {
          rv_vec.push_back(*it);
        }
      }
    }
  }

  // Check if there are any RVs in the functions.
  if(rv_vec.size() > 0) {
    // Add the RVs to the parameters list.
    for(auto it = rv_vec.begin(); it != rv_vec.end(); ++it) {
      params.push_back(*it);
    }
  }

  // Initialize Lambda functions.
  for(size_t i = 0; i < n_; i++) {
    v[i].init({params}, *equations[i]);
  }

  // Initialize the time counters.
  double t_begin   = options_.t_begin();
  double t_end     = options_.t_end();
  double t_current = t_begin;

  double step_size = options_.step_size();

  // Add the initial contition to the result.
  for(size_t i = 0; i < n_; i++) {
    x_result_.emplace_back(initial_condition_[i]);
  }

  // Add the initial time to the result.
  t_result_.push_back(t_current);

  std::vector<double> current_val;
  std::vector<double> last_val;
  last_val = x_result_;

  auto pos = current_val.begin();
  auto rv_pos = current_val.end();

  // Main ODE loop.
  do {
    // Get the current n values.
    current_val = last_val;

    pos = current_val.begin();
    pos = current_val.insert(pos, t_current);
    // current_val[0] = t_current;

    if(rv_vec.size() > 0) {
      rv_pos = current_val.end();
      for (auto it = rv_vec.begin(); it != rv_vec.end(); ++it) {
        rv_pos = current_val.insert(rv_pos, SymEngine::rcp_dynamic_cast<const Math::RandomVariable>(*it)->sample(gen));
      }
    }

    // Evaluate the state functions.
    for(size_t i = 0; i < n_; i++) {
      // Store the result in last_val.
      last_val[i] += step_size * v[i].call(current_val);
      // Add the result to the result vector.
      x_result_.push_back(last_val[i]);
    }

    // Advance the time.
    t_current += step_size;
    t_result_.push_back(t_current);

  } while(t_current <= t_end);
}

// ----------------------------------------------------------------------
// ode_euler
//
void ode_euler(StateSpace &sys,
               std::vector<double> x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result) {
  //
  ode_options options;
  EulerVisitor v(x0, t_result, x_result, options);
  sys.accept(v);
}

void ode_euler(StateSpace &sys,
               std::vector<double> x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result,
               ode_options options) {
  //
  EulerVisitor v(x0, t_result, x_result, options);
  sys.accept(v);
}

} // Controls
