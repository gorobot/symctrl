#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symctrl/assert.hpp>
#include <symctrl/shims/hash.hpp>

using Controls::hash_t;
using Controls::hash_string;

// Uncomment this line to enable debugging.
#define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

// class AbstractBase {
// public:
//   virtual ~AbstractBase() {}
//
//   virtual AbstractBase& someVirtualCall() = 0;
// };
//
// class Derived;
// void do_something(Derived &m);
//
// class Derived
//     : public AbstractBase {
// public:
//   Derived() {}
//   Derived(Derived &m) {}
//   Derived &operator=(Derived &m) { return *this; }
//
//   virtual Derived& someVirtualCall() override {
//     std::cout << "calling Derived virtual function." << '\n';
//     // do_something(*this);
//     // return new Derived(*this);
//     return static_cast<Derived &>(*this);
//     // auto ret = static_cast<Derived &>(*this);
//     // decltype(ret)::show;
//     // return ret;
//   }
//
//   void say_hello() {
//     std::cout << "hello" << '\n';
//   }
// };
//
// void do_something(Derived &m) {
//   m.say_hello();
// }
//
// // template<typename Derived>
// // class CRTPBase
// //     : public AbstractBase {
// // public:
// //   using Type = CRTPBase<Derived>;
// //
// //   inline Derived &operator~() {
// //     return *static_cast<Derived *>(this);
// //   }
// //
// //   inline const Derived &operator~() const {
// //     return *static_cast<const Derived *>(this);
// //   }
// //
// //   CRTPBase<Derived>& someVirtualCall() override {
// //     std::cout << "calling CRTPBase virtual function." << '\n';
// //     return static_cast<CRTPBase<Derived> &>(*this);
// //   }
// // };
// //
// // class CRTPDerived
// //     : public CRTPBase<CRTPDerived> {
// // public:
// //   using Type = CRTPDerived;
// //
// //   CRTPDerived() {}
// //
// //   CRTPDerived& someVirtualCall() override {
// //     std::cout << "calling CRTPDerived virtual function." << '\n';
// //     return static_cast<CRTPDerived &>(*this);
// //   }
// //
// //   void say_hello() {
// //     std::cout << "hello" << '\n';
// //   }
// // };
//
// TEST_CASE("Playground", "[playground]") {
//   // CRTPDerived A;
//   // AbstractBase *ptr1 = &A;
//   // ptr1->someVirtualCall();
//
//   Derived B;
//   AbstractBase *ptr2 = &B;
//   // (*ptr2).someVirtualCall();
//   // auto C = ptr2->someVirtualCall();
//   // do_something(ptr2->someVirtualCall());
//   // decltype(ptr2->someVirtualCall())::show;
// }

class base_sym
    : public std::enable_shared_from_this<base_sym> {
public:
  virtual ~base_sym() {}

  inline std::shared_ptr<base_sym> as_ptr();

  virtual std::string as_str() const = 0;
  virtual hash_t hash() const = 0;

private:
  // virtual base_sym *as_ptr_impl() const = 0;
};

inline std::shared_ptr<base_sym> base_sym::as_ptr() {
  std::cout << "somehow I'm here." << '\n';
  return shared_from_this();
}

// ----------------------------------------------------------------------
// sym
//
template<typename DT>
class crtp_sym
    : public base_sym {
public:
  inline DT &operator~();
  inline const DT &operator~() const;

  inline std::shared_ptr<DT> as_ptr();

  std::string as_str() const override;
  hash_t hash() const override;

private:
  // virtual crtp_sym *as_ptr_impl() const override {}
};

template<typename DT>
inline DT &crtp_sym<DT>::operator~() {
  std::cout << "crtp deref" << '\n';
  return *static_cast<DT *>(this);
}

template<typename DT>
inline const DT &crtp_sym<DT>::operator~() const {
  std::cout << "crtp const deref" << '\n';
  return *static_cast<const DT *>(this);
}

template<typename DT>
inline std::shared_ptr<DT> crtp_sym<DT>::as_ptr() {
  std::cout << "I want to be here." << '\n';
  // return static_cast<DT &>(*this).shared_from_this();
  return std::static_pointer_cast<DT>(shared_from_this());
}

template<typename DT>
std::string crtp_sym<DT>::as_str() const {
  std::cout << "getting string in virtual method." << '\n';
  return static_cast<const DT &>(*this).as_str_();
}

template<typename DT>
hash_t crtp_sym<DT>::hash() const {
  return static_cast<const DT &>(*this).get_hash();
}

// ----------------------------------------------------------------------
// sym
//
class sym
    : public crtp_sym<sym> {
public:
  using this_type = sym;

private:
  std::string name_;

  hash_t hash_;

public:
  explicit inline sym();
  explicit inline sym(std::string name);
  inline sym(const sym &m);

  inline sym &operator=(std::string name);
  inline sym &operator=(const sym &rhs);

  inline std::string as_str_() const;
  inline operator std::string() const;

  inline hash_t get_hash() const;
};

// ----------------------------------------------------------------------
// sym Constructor
//
inline sym::sym()
    : name_(std::string()),
      hash_(0) {
  SYMCTRL_DEBUG("sym default constructor");
}

inline sym::sym(const sym &m)
    : name_(m.name_),
      hash_(m.hash_) {
  SYMCTRL_DEBUG("sym copy constructor");
}

inline sym::sym(std::string name)
    : name_(name),
      hash_(hash_string{}(name)) {
  SYMCTRL_DEBUG("sym copy constructor");
}

// ----------------------------------------------------------------------
// sym Assignment Operator
//
inline sym &sym::operator=(const sym &rhs) {
  SYMCTRL_DEBUG("sym copy assignment operator");
  name_ = rhs.as_str();
  hash_ = rhs.hash();
  return *this;
}

inline sym &sym::operator=(std::string name) {
  SYMCTRL_DEBUG("sym copy assignment operator");
  name_ = name;
  hash_ = hash_string{}(name);
  return *this;
}

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
inline std::string sym::as_str_() const {
  return name_;
}

inline sym::operator std::string() const {
  return this->as_str();
}

inline hash_t sym::get_hash() const {
  return hash_;
}

// ----------------------------------------------------------------------
// sym_t
//
class sym_t
    : public crtp_sym<sym_t> {
public:

private:
  std::shared_ptr<base_sym> ptr_;

public:
  explicit inline sym_t(std::string name);

  template<typename DT>
  inline sym_t(crtp_sym<DT> &m);
  template<typename DT>
  inline sym_t(const crtp_sym<DT> &&m);

  inline sym_t(sym_t &m);
  inline sym_t(sym_t &&m);

  inline sym_t &operator=(std::string name);

  template<typename DT>
  inline sym_t &operator=(crtp_sym<DT> &rhs);
  // inline sym_t &operator=(sym &&rhs);

  inline std::string as_str_() const;
  // inline operator std::string() const;

  inline hash_t get_hash() const;
};

// ----------------------------------------------------------------------
// sym_t Constructor
//
inline sym_t::sym_t(std::string name)
    : ptr_(std::make_shared<sym>(name)) {}

template<typename DT>
inline sym_t::sym_t(crtp_sym<DT> &m)
    : ptr_((~m).as_ptr()) {}

template<typename DT>
inline sym_t::sym_t(const crtp_sym<DT> &&m)
    : ptr_(std::make_shared<DT>(std::move(~m))) {}

inline sym_t::sym_t(sym_t &m)
    : ptr_(m.ptr_->as_ptr()) {}

inline sym_t::sym_t(sym_t &&m)
    : ptr_(std::move(m.ptr_->as_ptr())) {}

// ----------------------------------------------------------------------
// sym_t Assignment Operator
//
inline sym_t &sym_t::operator=(std::string name) {
  ptr_ = std::make_shared<sym>(name);
  return *this;
}

template<typename DT>
inline sym_t &sym_t::operator=(crtp_sym<DT> &m) {
  ptr_ = (~m).as_ptr();
  return *this;
}

// inline sym_t &sym_t::operator=(sym &&m) {
//   ptr_ = m.as_ptr();
//   return *this;
// }

// ----------------------------------------------------------------------
// sym_t Member Function Definitions
//
inline std::string sym_t::as_str_() const {
  return ptr_->as_str();
}

// inline sym_t::operator std::string() const {
//   return this->as_str();
// }

inline hash_t sym_t::get_hash() const {
  return ptr_->hash();
}

// ----------------------------------------------------------------------
// Expression
//
template<typename DT>
class Expression {};

// ----------------------------------------------------------------------
// SymbolicAdd
//
template<typename T1, typename T2>
class SymbolicAdd
    : public crtp_sym<SymbolicAdd<T1, T2>> {
private:
  const T1 &lhs_;
  const T2 &rhs_;

public:
  SymbolicAdd(const crtp_sym<T1> &lhs, const crtp_sym<T2> &rhs)
      : lhs_(~lhs),
        rhs_(~rhs) {}

  inline std::string as_str_() const {
    SYMCTRL_DEBUG("getting the expression string.");
    return (~lhs_).as_str() + " + " + (~rhs_).as_str();
  }

  inline hash_t get_hash() const {
    return 0;
  }
};

template<typename T1, typename T2>
inline auto operator+(const crtp_sym<T1> &lhs, const crtp_sym<T2> &rhs)
-> const SymbolicAdd<T1, T2> {
  return SymbolicAdd<T1, T2>(~lhs, ~rhs);
}

TEST_CASE("playground", "[playground]") {
  sym_t x("x");
  sym_t y("y");
  sym_t z("z");
  // sym_t z = x;
  sym_t a = x + y;
  std::cout << a.as_str() << '\n';
  sym_t b = a + x;
  std::cout << b.as_str() << '\n';
  sym_t c = x + y + z;
  // REQUIRE(b == a + x);
}
