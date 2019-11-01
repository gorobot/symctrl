#ifndef SYMCTRL_MATH_RANDOM_RANDOM_VARIABLE_HPP
#define SYMCTRL_MATH_RANDOM_RANDOM_VARIABLE_HPP

// #include <symengine/basic.h>
// #include <symengine/symbol.h>

#include <symctrl/math/random/random_distribution.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// RandomVariable
//
class RandomVariable : public SymEngine::Symbol {
public:
  using SymbolType = SymEngine::RCP<const SymEngine::Symbol>;
  using RandomVariableType = SymEngine::RCP<const RandomVariable>;

private:
  RandomNumberDistribution *dist_;

public:
  explicit inline RandomVariable(SymbolType &s,
                                 RandomNumberDistribution *dist);
  explicit inline RandomVariable(const std::string &name,
                                 RandomNumberDistribution *dist);

  double sample(std::random_device &gen) const {
    return sample_distribution(*dist_, gen);
  }
};

inline RandomVariable::RandomVariable(SymbolType &s,
                                      RandomNumberDistribution *dist) :
                                      SymEngine::Symbol(s->get_name()),
                                      dist_(dist) {
  //
}

inline RandomVariable::RandomVariable(const std::string &name,
                                      RandomNumberDistribution *dist) :
                                      SymEngine::Symbol(name),
                                      dist_(dist) {
  //
}

inline RandomVariable::RandomVariableType
random_variable(const std::string &name,
                RandomNumberDistribution *dist) {
    return SymEngine::make_rcp<const RandomVariable>(name, dist);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_RANDOM_RANDOM_VARIABLE_HPP
