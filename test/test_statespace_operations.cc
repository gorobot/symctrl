#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/math/random/random_variable.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/systems/statespace.hpp>
#include <symctrl/shims/equal.hpp>
#include <symctrl/shims/symbolic.hpp>
#include <symctrl/shims/parse.hpp>

using Controls::Math::BlockMatrix;
using Controls::controllability_matrix;
using Controls::equal;
using Controls::linearize;
using Controls::Math::SymbolicDense;
using Controls::observability_matrix;
using Controls::parse;
using Controls::StateSpace;
using Controls::symbolic_t;
using Controls::symbolic_symbol_t;

using SymEngine::Basic;
using SymEngine::RCP;
using SymEngine::symbol;
using SymEngine::Symbol;

TEST_CASE("StateSpace Operations: Controllability", "[statespace_ops]") {
  StateSpace sys({parse("x1"), parse("x2")},
                 {parse("u")},
                 {parse("x2"), parse("-sin(x1) - x2 + u")},
                 {parse("x1"), parse("x2")});

  StateSpace linsys = linearize(sys);

  BlockMatrix<symbolic_t> Co = controllability_matrix(linsys);

  REQUIRE(Co.as_dense() == SymbolicDense(2, 2, {parse("0"),   parse("1"),
                                                parse("1"),   parse("-1")}));
}

TEST_CASE("StateSpace Operations: Linearize", "[statespace_ops]") {
  StateSpace sys({parse("x1"), parse("x2")},
                 {parse("u")},
                 {parse("x2"), parse("-sin(x1) - x2 + u")},
                 {parse("x1"), parse("x2")});

  StateSpace linsys = linearize(sys);

  SymbolicDense A = state_matrix(linsys);
  SymbolicDense B = input_matrix(linsys);
  SymbolicDense C = output_matrix(linsys);
  SymbolicDense D = feedforward_matrix(linsys);

  REQUIRE(A == SymbolicDense(2, 2, {parse("0"),         parse("1"),
                                    parse("-1"),        parse("-1")}));

  REQUIRE(B == SymbolicDense(2, 1, {parse("0"),
                                    parse("1")}));

  REQUIRE(C == SymbolicDense(2, 2, {parse("1"),         parse("0"),
                                    parse("0"),         parse("1")}));

  REQUIRE(D == SymbolicDense(2, 1, {parse("0"),
                                    parse("0")}));
}

TEST_CASE("StateSpace Operations: obsv", "[statespace_ops]") {
  StateSpace sys({parse("x1"), parse("x2")},
                 {parse("u")},
                 {parse("x2"), parse("-sin(x1) - x2 + u")},
                 {parse("x1"), parse("x2")});

  StateSpace linsys = linearize(sys);

  BlockMatrix<symbolic_t> Ob = observability_matrix(linsys);

  REQUIRE(Ob.as_dense() == SymbolicDense(4, 2, {parse("1"),   parse("0"),
                                                parse("0"),   parse("1"),
                                                parse("0"),   parse("1"),
                                                parse("-1"),  parse("-1")}));
}
