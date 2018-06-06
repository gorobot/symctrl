#ifndef SYMCTRL_TRANSFER_FUNCTION_HPP
#define SYMCTRL_TRANSFER_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>

#include "system.hpp"

namespace Controls {

class TransferFunction : public System {
public:
  TransferFunction();
  ~TransferFunction();

  void set_num(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);
  void set_den(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);

  // void add_num(SymEngine::RCP<const SymEngine::Basic> arg);
  // void add_den(SymEngine::RCP<const SymEngine::Basic> arg);

  std::vector<SymEngine::RCP<const SymEngine::Basic>> get_num();
  std::vector<SymEngine::RCP<const SymEngine::Basic>> get_den();

  void accept(SystemVisitor &visitor);

private:
  std::vector<SymEngine::RCP<const SymEngine::Basic>> num_;
  std::vector<SymEngine::RCP<const SymEngine::Basic>> den_;
};

} // Controls

#endif /* end of include guard: SYMCTRL_TRANSFER_FUNCTION_HPP */
