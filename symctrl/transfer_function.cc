#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>
#include <symengine/subs.h>

#include "transfer_function.hpp"

using Controls::TransferFunction;

namespace Controls {

TransferFunction::TransferFunction() {}

TransferFunction::~TransferFunction() {}

void TransferFunction::set_num(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg) {
  num_ = arg;
}

void TransferFunction::set_den(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg) {
  den_ = arg;
}

std::vector<SymEngine::RCP<const SymEngine::Basic>> TransferFunction::get_num() {
  return num_;
}

std::vector<SymEngine::RCP<const SymEngine::Basic>> TransferFunction::get_den() {
  return den_;
}

} // Controls
