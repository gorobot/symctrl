#ifndef SYMCTRL_SYSTEMS_VISITORS_COEFFS_HPP
#define SYMCTRL_SYSTEMS_VISITORS_COEFFS_HPP

#include <vector>

#include <symengine/basic.h>
#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/pow.h>

#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// CoeffsVisitor
//
class CoeffsVisitor {
private:

  symbolic_t var_;
  std::vector<symbolic_t> coeffs_;

public:
  CoeffsVisitor(symbolic_t var);

  void bvisit(const SymEngine::Add &m);
  void bvisit(const SymEngine::Mul &m);
  void bvisit(const SymEngine::Pow &m);
  void bvisit(const SymEngine::Basic &m);

  std::vector<symbolic_t> apply(symbolic_t f);
};

std::vector<symbolic_t> coeffs(symbolic_t f, symbolic_t var) {
  CoeffsVisitor s(var);
  s.accept(*f);

}

} // Controls

#endif // SYMCTRL_SYSTEMS_VISITORS_COEFFS_HPP
