#ifndef SYMCTRL_ODE_OPTIONS_OPTIONS_HPP
#define SYMCTRL_ODE_OPTIONS_OPTIONS_HPP

#include <symctrl/assert.hpp>

namespace Controls {

#define GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define DECL(...) GET_MACRO(__VA_ARGS__, DECL5, DECL4, DECL3)(__VA_ARGS__)
#define CTOR(...) GET_MACRO(__VA_ARGS__, CTOR5, CTOR4, CTOR3)(__VA_ARGS__)
#define GETT(...) GET_MACRO(__VA_ARGS__, GETT5, GETT4, GETT3)(__VA_ARGS__)
#define SETT(...) GET_MACRO(__VA_ARGS__, SETT5, SETT4, SETT3)(__VA_ARGS__)

// Because there are an indeterminate amount of member variables, this macro
// defines the variable, its type, its default value, and its upper and lower
// limits. These will be propagated throughout the struct definition.
//
// MACRO(Type, Name, Value)
// MACRO(Type, Name, Value, Lower)          (checks Lower <= Value)
// MACRO(Type, Name, Value, Lower, Upper)   (checks Lower <= Value < Upper)
#define ODE_OPTIONS_ENUM(MACRO) \
MACRO(double, step_size, 0.01,  1e-6, 1e6) \
MACRO(double, t_begin,   0,     0) \
MACRO(double, t_end,     10)

// ----------------------------------------------------------------------
// ode_options
//
struct ode_options {
private:
  #define DECL3(Type, Name, Value) Type Name##_;
  #define DECL4(Type, Name, Value, Upper) Type Name##_;
  #define DECL5(Type, Name, Value, Upper, Lower) Type Name##_;
  ODE_OPTIONS_ENUM(DECL)
  #undef DECL3
  #undef DECL4
  #undef DECL5
  #undef DECL

public:
  ode_options() {
    #define CTOR3(Type, Name, Value) Name##_ = Value;
    #define CTOR4(Type, Name, Value, Upper) Name##_ = Value;
    #define CTOR5(Type, Name, Value, Upper, Lower) Name##_ = Value;
    ODE_OPTIONS_ENUM(CTOR)
    #undef CTOR3
    #undef CTOR4
    #undef CTOR5
    #undef CTOR
  }

  #define GETT3(Type, Name, Value) \
  void Name(const Type Name) { \
    Name##_ = Name; \
  }
  #define GETT4(Type, Name, Value, Lower) \
  void Name(const Type Name) { \
    SYMCTRL_ASSERT(Lower <= Name); \
    Name##_ = Name; \
  }
  #define GETT5(Type, Name, Value, Lower, Upper) \
  void Name(const Type Name) { \
    SYMCTRL_ASSERT(Lower <= Name && Name < Upper); \
    Name##_ = Name; \
  }
  ODE_OPTIONS_ENUM(GETT)
  #undef GETT3
  #undef GETT4
  #undef GETT5
  #undef GETT

  #define SETT3(Type, Name, Value) \
  const Type& Name() const { return Name##_; }
  #define SETT4(Type, Name, Value, Lower) \
  const Type& Name() const { return Name##_; }
  #define SETT5(Type, Name, Value, Lower, Upper) \
  const Type& Name() const { return Name##_; }
  ODE_OPTIONS_ENUM(SETT)
  #undef SETT3
  #undef SETT4
  #undef SETT5
  #undef SETT
};

#undef GET_MACRO

} // Controls

#endif // SYMCTRL_ODE_OPTIONS_OPTIONS_HPP
