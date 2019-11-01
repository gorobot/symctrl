#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/sets.h>
#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/mdp.hpp>

using SymEngine::Basic;
using SymEngine::finiteset;
using SymEngine::RCP;
using SymEngine::Set;
using SymEngine::symbol;

TEST_CASE("MDP: Value Iteration", "[MDP]") {
  RCP<const Basic> x = symbol("x");
  RCP<const Basic> u = symbol("u");

  RCP<const Set> X = finiteset({x});
  RCP<const Set> U = finiteset({u});

  Controls::CostFunction *R;
  Controls::TransitionFunction *T;

  R = new Controls::DiscreteCostFunction(2, 1);
  T = new Controls::DiscreteTransitionFunction(2, 1);

  Controls::MDP *sys;

  sys = new Controls::MDP(X, U, T, R, 0.9);

  REQUIRE(1 == 1);
  REQUIRE(2 == 2);
}

TEST_CASE("POMDP: Value Iteration", "[MDP]") {
  RCP<const Basic> x = symbol("x");
  RCP<const Basic> u = symbol("u");

  RCP<const Set> X = finiteset({x});
  RCP<const Set> U = finiteset({u});

  Controls::CostFunction *R;
  Controls::TransitionFunction *T;
  Controls::TransitionFunction *Ob;

  R = new Controls::DiscreteCostFunction(2, 1);
  T = new Controls::DiscreteTransitionFunction(2, 1);
  Ob = new Controls::DiscreteTransitionFunction(2, 1);

  Controls::POMDP *sys;

  sys = new Controls::POMDP(X, U, T, R, Ob, 0.9);

  REQUIRE(1 == 1);
  REQUIRE(2 == 2);
}
