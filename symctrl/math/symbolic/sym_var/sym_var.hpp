#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_VAR_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_VAR_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/recover.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_var
//
class sym_var
    : public Symbolic<sym_var> {
public:
  using Type = sym_var;

  static constexpr bool isNumeric = false;
  static constexpr bool isComplex = false;

  static inline constexpr bool canEvaluate() noexcept { return false; }

private:
  std::string name_;

  hash_t hash_;

public:
  explicit inline sym_var();
  inline sym_var(std::string name);

  inline std::string as_str() const;
  inline hash_t hash() const;

private:
  // friend type recover<type>(std::shared_ptr<void>);
};

// ----------------------------------------------------------------------
// sym_var Constructor
//
inline sym_var::sym_var()
    : name_(std::string()),
      hash_(0) {}

inline sym_var::sym_var(std::string name)
    : name_(name),
      hash_(hash_string{}(name)) {}

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
inline std::string sym_var::as_str() const {
  return name_;
}

inline hash_t sym_var::hash() const {
  return hash_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_VAR_HPP
