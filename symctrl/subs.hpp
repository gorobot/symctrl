#ifndef SYMCTRL_SUBS_HPP
#define SYMCTRL_SUBS_HPP

#include <symengine/dict.h>
#include <symengine/subs.h>

#include "visitor.hpp"

namespace Controls {

void subs(System &m,
          const SymEngine::RCP<const SymEngine::Basic> key,
          const SymEngine::RCP<const SymEngine::Basic> map);

class SubsVisitor : public SystemVisitor {
private:
  const SymEngine::RCP<const SymEngine::Basic> key_, map_;

public:
  SubsVisitor(const SymEngine::RCP<const SymEngine::Basic> key,
              const SymEngine::RCP<const SymEngine::Basic> map) : key_(key), map_(map) {}

  virtual void visit(StateSpace &m) {
    size_t n = m.get_num_f();
    size_t p = m.get_num_g();

    SymEngine::map_basic_basic d;
    d[key_] = map_;

    size_t i = 0;
    for(i = 0; i < n; i++) {
      m.set_f(i, SymEngine::ssubs(m.get_f(i), d));
    }

    for(i = 0; i < p; i++) {
      m.set_g(i, SymEngine::ssubs(m.get_g(i), d));
    }
  }

  virtual void visit(TransferFunction &m) {}
};

void subs(System &m,
          const SymEngine::RCP<const SymEngine::Basic> key,
          const SymEngine::RCP<const SymEngine::Basic> map) {
  //
  SubsVisitor s(key, map);
  m.accept(s);
}

} // Controls

#endif /* end of include guard: SYMCTRL_SUBS_HPP */
