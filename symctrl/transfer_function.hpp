#ifndef SYMCTRL_TRANSFER_FUNCTION_HPP
#define SYMCTRL_TRANSFER_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>

#include "system.hpp"

namespace Controls {

class TransferFunction : public System {
public:
  TransferFunction();
  TransferFunction(const SymEngine::RCP<const SymEngine::Basic> arg) : var_(arg) {};
  ~TransferFunction();

  void set_var(const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_var();

  void add_num(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_num(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_num(size_t n);
  // void remove_num(size_t n);
  size_t get_num_nums();

  void add_den(const SymEngine::RCP<const SymEngine::Basic> arg);
  void set_den(size_t n, const SymEngine::RCP<const SymEngine::Basic> arg);
  SymEngine::RCP<const SymEngine::Basic> get_den(size_t n);
  // void remove_den(size_t n);
  size_t get_num_dens();

  void accept(SystemVisitor &visitor);

private:
  SymEngine::RCP<const SymEngine::Basic> var_;

  SymEngine::vec_basic num_;
  SymEngine::vec_basic den_;
};

void transferfunction_poles();
void transferfunction_zeros();

void minimal_realization();

} // Controls

#endif /* end of include guard: SYMCTRL_TRANSFER_FUNCTION_HPP */
