#ifndef SYMCTRL_MDP_TRAIN_HPP
#define SYMCTRL_MDP_TRAIN_HPP

#include <map>
#include <tuple>
#include <vector>

#include "visitor.hpp"

namespace Controls {

typedef std::vector<std::vector<double>> mdp_policy_t;

void policy_iteration(MDP &m);
void value_iteration(MDP &m,
                     const size_t horizon, const double tolerance,
                     mdp_policy_t policy);

void value_approximation(MDP &m);

class MDPTrainVisitor : public MDPVisitor {
public:
  mdp_policy_t policy_;

  void init_random_policy(MDP &m);
};

// Policy iteration.
class PolicyIterationVisitor : public MDPTrainVisitor {
private:

public:
  PolicyIterationVisitor() {
    //
  }
  ~PolicyIterationVisitor() {}

  virtual void visit(MDP &m);
};

// Value iteration.
class ValueIterationVisitor : public MDPTrainVisitor {
private:
  const size_t horizon_;
  const double tolerance_;
public:
  ValueIterationVisitor(const size_t horizon,
                        const double tolerance) : horizon_(horizon), tolerance_(tolerance) {
    //
  }
  ~ValueIterationVisitor() {}

  virtual void visit(MDP &m);
};

void value_iteration(MDP &m,
                     const size_t horizon, const double tolerance,
                     mdp_policy_t policy) {
  ValueIterationVisitor s(horizon, tolerance);
  m.accept(s);

  policy = s.policy_;
}

} // Controls

#endif /* end of include guard: SYMCTRL_MDP_TRAIN_HPP */
