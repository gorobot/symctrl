#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP

#include <memory>
#include <string>

#include <typeinfo>

#include <type_traits>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/sym_var/sym_var.hpp>
#include <symctrl/math/symbolic/sym_number/sym_number.hpp>
// #include <symctrl/math/symbolic/sym_t/type_id.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_numeric.hpp>
#include <symctrl/type_traits/is_string.hpp>
// #include <symctrl/type_traits/is_safely_castable.hpp>
#include <symctrl/shims/void_t.hpp>

namespace Controls {
namespace Math {

class sym_t;

// ----------------------------------------------------------------------
// sym_t
//
class sym_t
    : public Symbolic<sym_t> {
public:
  using Type = sym_t;

  static constexpr bool isNumeric = false;

private:
  class Concept {
  private:

  public:
    virtual ~Concept() = default;

    virtual std::string as_str() const = 0;
    virtual hash_t hash() const = 0;
    virtual bool canEvaluate() const = 0;
  };

  template<typename T>
  class Model final
      : public Concept {
  public:
    using Type = typename T::Type;

  private:
    T data_;

  public:
    inline Model(T m)
        : data_(m) {}

    virtual std::string as_str() const override {
      return data_.as_str();
    }
    virtual hash_t hash() const override {
      return data_.hash();
    }
    virtual bool canEvaluate() const override {
      return data_.canEvaluate();
    }
  };

  // // https://github.com/jbcoe/polymorphic_value
  // template<template<typename...> class T, typename U, typename V>
  // class Model<T<U, V>> final
  //     : public Concept {
  // public:
  //   using type = T<U, V>;
  //
  // private:
  //   // U lhs_data_;
  //   // V rhs_data_;
  //   T<U, V> data_;
  //
  // public:
  //   // inline Model(T<U, V> m)
  //   //     : lhs_data_(m.lhs_),
  //   //       rhs_data_(m.rhs_) {}
  //   inline Model(T<U, V> m)
  //       : data_(m) {}
  //
  //   virtual std::string as_str() const override {
  //     return data_.as_str();
  //   }
  //   virtual hash_t hash() const override {
  //     return data_.hash();
  //   }
  //
  //   virtual bool canEvaluate() const override {
  //     return data_.canEvaluate();
  //   }
  // };

  std::shared_ptr<const Concept> ptr_;

public:
  template<typename T, enable_if_string_t<T, int> = 0>
  explicit inline sym_t(T m);

  template<typename T, enable_if_numeric_t<T, int> = 0>
  inline sym_t(T m);

  template<typename DT>
  inline sym_t(const Symbolic<DT> &m);
  template<typename DT>
  inline sym_t(Symbolic<DT> &&m);

  template<typename DT>
  inline sym_t &operator=(const Symbolic<DT> &rhs);
  template<typename DT>
  inline sym_t &operator=(Symbolic<DT> &&rhs);

  inline std::string as_str() const;
  inline hash_t hash() const;
  inline bool canEvaluate() const;

  // template<typename DT>
  // friend inline void apply_(Symbolic<DT> &lhs, const sym_t &rhs) {
  //   SYMCTRL_DEBUG("sym_t::apply_");
  //   // apply_f(~lhs, *rhs.ptr_);
  //   // rhs.apply_f2(~lhs);
  //   // auto v = ApplyVisitor<DT>(~lhs);
  // }
  // template<typename DT>
  // friend inline void apply_add_(Symbolic<DT> &lhs, const sym_t &rhs) {
  //   SYMCTRL_DEBUG("sym_t::apply_add_");
  //   // apply_f(~lhs, *rhs.ptr_);
  //   // rhs.apply_f2(~lhs);
  //   // auto v = ApplyVisitor<DT>(~lhs);
  // }
};

// ----------------------------------------------------------------------
// sym_t Constructor
//
template<typename T, enable_if_string_t<T, int>>
inline sym_t::sym_t(T m)
    : ptr_(std::make_shared<Model< sym_var >>(std::string(m))) {}

template<typename T, enable_if_numeric_t<T, int>>
inline sym_t::sym_t(T m)
    : ptr_(std::make_shared<Model< sym_number<T> >>(m)) {}

template<typename DT>
inline sym_t::sym_t(const Symbolic<DT> &m)
    : ptr_(std::make_shared<Model<DT>>(~m)) {}

template<typename DT>
inline sym_t::sym_t(Symbolic<DT> &&m)
    : ptr_(std::make_shared<Model<DT>>(std::move(~m))) {}

// ----------------------------------------------------------------------
// sym_t Assignment Operator
//
template<typename DT>
inline sym_t &sym_t::operator=(const Symbolic<DT> &rhs) {
  ptr_.reset();
  ptr_ = std::make_shared<Model<DT>>(~rhs);
  return *this;
}

template<typename DT>
inline sym_t &sym_t::operator=(Symbolic<DT> &&rhs) {
  ptr_.reset();
  ptr_ = std::make_shared<Model<DT>>(std::move(~rhs));
  return *this;
}

// ----------------------------------------------------------------------
// sym_t Member Function Definitions
//
inline std::string sym_t::as_str() const {
  return ptr_->as_str();
}

inline hash_t sym_t::hash() const {
  return ptr_->hash();
}

inline bool sym_t::canEvaluate() const {
  return ptr_->canEvaluate();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP
