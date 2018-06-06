// A hybrid system has several 'modes', where the dynamics of the system change.

#ifndef SYMCTRL_HYBRID_SYSTEM_HPP
#define SYMCTRL_HYBRID_SYSTEM_HPP

#include <map>
#include <tuple>
#include <vector>
#include <symengine/basic.h>
#include <symengine/matrix.h>

#include "system.hpp"

namespace Controls {

class HybridSystem : public System {
public:
  HybridSystem();
  ~HybridSystem();

  void add_state(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_state(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_state(size_t n);
  // void remove_state(size_t n);
  size_t get_num_states();

  void add_input(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_input(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_input(size_t n);
  // void remove_input(size_t n);
  size_t get_num_inputs();

  void add_f(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_f(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_f(size_t n);
  // void remove_f(size_t n);
  size_t get_num_f();

  void add_g(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_g(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_g(size_t n);
  // void remove_g(size_t n);
  size_t get_num_g();

  void set_num_modes(size_t r, size_t c, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_num_modes(size_t r, size_t c);

  void set_guard(size_t r, size_t c, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_guard(size_t r, size_t c);

  void accept(SystemVisitor &visitor);

protected:
  // Vector of symbolic state variables.
  std::vector<SymEngine::RCP<const SymEngine::Basic>> states_;

  // Vector of symbolic input variables.
  std::vector<SymEngine::RCP<const SymEngine::Basic>> inputs_;

  // Vector of state equations.
  // Each mode can have several state equations. These are mapped using a tuple.
  std::map<std::tuple<int, int>, SymEngine::RCP<const SymEngine::Basic>> f_;

  // Vector of output equations.
  std::vector<SymEngine::RCP<const SymEngine::Basic>> g_;

  size_t n_modes;

  vector<SymEngine::RCP<const SymEngine::Basic>> guards_
};

} // Controls

#endif /* end of include guard: SYMCTRL_HYBRID_SYSTEM_HPP */
