#ifndef SYMCTRL_ODE_RK45_HPP
#define SYMCTRL_ODE_RK45_HPP

#include <tuple>
#include <vector>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/lambda_double.h>

#include "ode_options.hpp"
#include "visitor.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Runge-Kutta 45
//
class RK45Visitor : public SystemVisitor {
private:
  std::tuple<unsigned, unsigned> &t_span_;
  SymEngine::vec_basic &x0_;

  std::vector<double> &t_result_;
  SymEngine::vec_basic &x_result_;

public:
  RK45Visitor(std::tuple<unsigned, unsigned> &t_span,
              SymEngine::vec_basic &x0,
              std::vector<double> &t_result,
              SymEngine::vec_basic &x_result) : t_span_(t_span), x0_(x0), t_result_(t_result), x_result_(x_result) {}

  ~RK45Visitor() {}

  virtual void visit(StateSpace &m) {
    size_t i;
    size_t n = m.get_num_f();

    std::vector<SymEngine::LambdaRealDoubleVisitor> v(n);

    std::vector<SymEngine::RCP<const SymEngine::Basic>> x;
    std::vector<SymEngine::RCP<const SymEngine::Basic>> f;

    x_result_.push_back(x0_);

    for(i = 0; i < n; i++) {
      x.push_back(m.get_state(i));
      f.push_back(m.get_f(i));
    }

    // Initialize Lambda functions.
    for(i = 0; i < n; i++) {
      v[i].init(x, *f[i]);
    }

    double t_begin = t_span_.front();
    double t_end = t_span_.back();

    double t_current = t_begin;

    double dt = 0.1;

    double k1, k2, k3, k4;

    // Main ODE loop.
    do {
      val = x_result_.back();
      res = SymEngine::vec_basic(n);

      t_last = t_current;
      t_current += dt;

      k1 = dt * v[i].call(val);
      k2 = dt *

    } while(t_current <= t_end);
  }
};

void ode_rk45(StateSpace &m,
          std::tuple<unsigned, unsigned> &t_span,
          SymEngine::vec_basic &x0,
          std::vector<double> &t_result,
          SymEngine::vec_basic &x_result) {
  //
  RK45Visitor v(t_span, x0, t_result, x_result);
  m.accept(v);
}

} // Controls

#endif // SYMCTRL_ODE_RK45_HPP
