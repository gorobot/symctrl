#ifndef SYMCTRL_SYSTEMS_FUNCTOR_FUNCTOR_HPP
#define SYMCTRL_SYSTEMS_FUNCTOR_FUNCTOR_HPP

#include <vector>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

// #include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/functor/functor.hpp>
#include <symctrl/math/functor/lambda.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Control Policy Signature
//
#ifndef CONTROL_POLICY_PARAMS
#define CONTROL_POLICY_PARAMS \
std::vector<double>, \
const std::vector<double> &
#endif

// ----------------------------------------------------------------------
// ControlPolicy
//
class ControlPolicy :
public Math::Functor<ControlPolicy, CONTROL_POLICY_PARAMS> {
public:
  using type = Math::BaseFunctor<CONTROL_POLICY_PARAMS>;

  virtual std::vector<double> eval(const std::vector<double> &state) = 0;
};

template<typename F>
inline ControlPolicy::type *control_policy(F&& f) {
  return new Math::LambdaFunctor<F, CONTROL_POLICY_PARAMS>(f);
}

template<typename T>
inline bool is_a_control_policy(T &b) {
  return dynamic_cast<ControlPolicy::type *>(&b) != nullptr;
}

// ----------------------------------------------------------------------
// Cost Function Signature
//
#ifndef COST_FUNCTION_PARAMS
#define COST_FUNCTION_PARAMS \
double, \
const std::vector<double> &, \
const std::vector<double> &
#endif

// ----------------------------------------------------------------------
// CostFunction
//
class CostFunction :
public Math::Functor<CostFunction, COST_FUNCTION_PARAMS> {
public:
  using type = Math::BaseFunctor<COST_FUNCTION_PARAMS>;

  virtual double eval(const std::vector<double> &state,
                      const std::vector<double> &input) = 0;
};

template<typename F>
inline CostFunction::type *cost_function(F&& f) {
  return new Math::LambdaFunctor<F, COST_FUNCTION_PARAMS>(f);
}

template<typename T>
inline bool is_a_cost_function(T &b) {
  return dynamic_cast<CostFunction::type *>(&b) != nullptr;
}

// ----------------------------------------------------------------------
// Transition Function Signature
//
#ifndef TRANSITION_FUNCTION_PARAMS
#define TRANSITION_FUNCTION_PARAMS \
std::vector<double>, \
const std::vector<double> &, \
const std::vector<double> &
#endif

// ----------------------------------------------------------------------
// TransitionFunction
//
class TransitionFunction :
public Math::Functor<TransitionFunction, TRANSITION_FUNCTION_PARAMS> {
public:
  using type = Math::BaseFunctor<TRANSITION_FUNCTION_PARAMS>;

  virtual std::vector<double> eval(const std::vector<double> &state,
                                   const std::vector<double> &input) = 0;
};

template<typename F>
inline TransitionFunction::type *transition_function(F&& f) {
  return new Math::LambdaFunctor<F, TRANSITION_FUNCTION_PARAMS>(f);
}

template<typename T>
inline bool is_a_transition_function(T &b) {
  return dynamic_cast<TransitionFunction::type *>(&b) != nullptr;
}

// // ----------------------------------------------------------------------
// // Discrete TransitionFunction
// //
// class DiscreteTransitionFunction :
// public TransitionFunction, public DenseMatrix<double> {
// public:
//   DiscreteTransitionFunction(const size_t n_states,
//                              const size_t n_inputs) :
//                              DenseMatrix<double>(n_states*n_inputs, n_states) {}
//   ~DiscreteTransitionFunction() {}
//
//   void eval(const std::vector<double> &state,
//             const std::vector<double> &input,
//             std::vector<double> &result) {
//     //
//     // Hash the state and input vector to come up with a unique identifier.
//     // The identifier corresponds to a specific row in the matrix.
//     // Return the result.
//   }
// };

// // ----------------------------------------------------------------------
// // Kernelized TransitionFunction
// //
// class KernelTransitionFunction : public TransitionFunction {
// private:
//   KernelFunction<double> &kernel_function_;
//
// public:
//   KernelTransitionFunction(KernelFunction<double> &K) : kernel_function_(K) {}
//   ~KernelTransitionFunction() {}
//
//   void eval(const std::vector<double> &state,
//             const std::vector<double> &input,
//             std::vector<double> &result) {
//     //
//     // Dot product in Hilbert space.
//   }
// };

} // Controls

#endif // SYMCTRL_SYSTEMS_FUNCTOR_FUNCTOR_HPP
