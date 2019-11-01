#ifndef SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERFUNCTION_HPP
#define SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERFUNCTION_HPP

#include <utility>
#include <vector>

#include <symengine/basic.h>
#include <symengine/mul.h>
#include <symengine/symbol.h>

#include <symctrl/systems/system.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// class BaseController;
//
// template<typename CT>
// class Controller : public BaseController;

// ----------------------------------------------------------------------
// TransferFunction
//
class TransferFunction : public System<TransferFunction> {
public:
  explicit inline TransferFunction();
  explicit inline TransferFunction(const symbolic_symbol_t v,
                                   const symbolic_t num,
                                   const symbolic_t den);

  inline TransferFunction(const TransferFunction &m);

  inline TransferFunction &operator=(const TransferFunction &rhs);

  inline TransferFunction &operator+=(const TransferFunction &rhs);
  inline TransferFunction &operator*=(const TransferFunction &rhs);

  inline operator symbolic_t() const;

private:
  // Transfer function variable.
  symbolic_symbol_t var_;

  // Separated numerator and denominator to avoid pole/zero cancellations.

  // Transfer function numerator.
  symbolic_t num_;

  // Transfer function denominator.
  symbolic_t den_;

public:
  inline symbolic_symbol_t var() const;

  inline symbolic_t &numerator();
  inline const symbolic_t &numerator() const;

  inline symbolic_t &denominator();
  inline const symbolic_t &denominator() const;

  // template<typename CT>
  // inline void apply_(Controller<CT> &controller);

  inline void accept(Visitor &visitor);
};

// ----------------------------------------------------------------------
// TransferFunction Constructor
//
inline TransferFunction::TransferFunction() {
  var_ = SymEngine::symbol("s");
  num_ = SymEngine::integer(1);
  den_ = SymEngine::integer(1);
}

inline TransferFunction::TransferFunction(const symbolic_symbol_t v,
                                          const symbolic_t num,
                                          const symbolic_t den) {
  //
  var_ = v;
  num_ = num;
  den_ = den;
}

inline TransferFunction::TransferFunction(const TransferFunction &m) {
  var_ = m.var_;
  num_ = m.num_;
  den_ = m.den_;
}

// ----------------------------------------------------------------------
// TransferFunction Assignment Operator
//
inline TransferFunction&
TransferFunction::operator=(const TransferFunction &rhs) {
  var_ = rhs.var_;
  num_ = rhs.num_;
  den_ = rhs.den_;

  return *this;
}

// ----------------------------------------------------------------------
// TransferFunction Member Function Definitions
//
inline TransferFunction::operator symbolic_t() const {
  return SymEngine::div(num_, den_);
}

inline symbolic_symbol_t TransferFunction::var() const {
  return var_;
}

inline symbolic_t &TransferFunction::numerator() {
  return num_;
}

inline const symbolic_t &TransferFunction::numerator() const {
  return num_;
}

inline symbolic_t &TransferFunction::denominator() {
  return den_;
}

inline const symbolic_t &TransferFunction::denominator() const {
  return den_;
}

} // Controls

#endif // SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERFUNCTION_HPP
