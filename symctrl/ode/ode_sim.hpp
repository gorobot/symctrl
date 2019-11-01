#ifndef SYMCTRL_ODE_SIM_HPP
#define SYMCTRL_ODE_SIM_HPP

#include <tuple>
#include <vector>
#include <symengine/lambda_double.h>

#include "visitor.hpp"

namespace Controls {

void odesim(StateSpace &m,
            std::vector<double> &x0,
            std::tuple<unsigned, unsigned> &t_span,
            std::vector<double> &t,
            std::vector<std::vector<double>> &x);

class OdeSimVisitor : public SystemVisitor {
private:
  std::vector<double> &x0_;
  std::tuple<unsigned, unsigned> &t_span_;

  std::vector<double> &time_;
  std::vector<std::vector<double>> &result_;

public:
  OdeSimVisitor(std::vector<double> &x0,
                std::tuple<unsigned, unsigned> &t_span,
                std::vector<double> &t,
                std::vector<std::vector<double>> &x) : x0_(x0), t_span_(t_span), time_(t), result_(x) {
    //
  }
  ~OdeSimVisitor() {}

  // std::vector<double> get_time_vector() {
  //   return time_;
  // }

  // std::vector<std::vector<double>> get_result_vector() {
  //   return result_;
  // }

  virtual void visit(StateSpace &m) {
    size_t n = m.get_num_states();
    std::vector<SymEngine::LambdaRealDoubleVisitor> v(n);
    std::vector<SymEngine::RCP<const SymEngine::Basic>> x;
    std::vector<SymEngine::RCP<const SymEngine::Basic>> f;

    // TODO: Check x0 size. Make sure that it is n.
    result_.push_back(x0_);

    std::vector<double> val;
    std::vector<double> res;

    // Get states and state equations.
    size_t i;
    for(i = 0; i < n; i++) {
      x.push_back(m.get_state(i));
      f.push_back(m.get_f(i));
    }

    // Initialize Lambda functions.
    for(i = 0; i < n; i++) {
      v[i].init(x, *f[i]);
    }

    double dt, t_last;
    double t_begin = t_span_.front();
    double t_end = t_span_.back();

    double t_current = t_begin;

    // Main ODE loop.
    do {
      val = result_.back();
      res = std::vector<double>(n);

      t_last = t_current;
      // TODO: Find time step here. Runge-Kutta algorithm.
      t_current++;
      dt = t_current - t_last;

      // Get dx/dt values.
      for(i = 0; i < n; i++) {
        res[i] = v[i].call(val)*dt;
      }

      // Add res to sequence of results.
      result_.push_back(res);

    } while(t_current <= t_end);

  }
};

// odesim visitor function.
void odesim(StateSpace &m,
            std::vector<double> &x0,
            std::tuple<unsigned, unsigned> &t_span,
            std::vector<double> &t,
            std::vector<std::vector<double>> &x) {
  //
  OdeSimVisitor s(x0, t_span, t, x);
  m.accept(s);

  // t = s.get_time_vector();
  // x = s.get_result_vector();
}

} // Controls

#endif // SYMCTRL_ODE_SIM_HPP
