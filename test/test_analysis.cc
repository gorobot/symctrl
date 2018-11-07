#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/analysis.hpp>

TEST_CASE("Analysis: ctrb", "[analysis]") {
  Controls::StateSpace *ss = new Controls::StateSpace();

  SymEngine::RCP<const SymEngine::Symbol> x1 = SymEngine::symbol("x1");
  SymEngine::RCP<const SymEngine::Symbol> x2 = SymEngine::symbol("x2");

  SymEngine::RCP<const SymEngine::Symbol> u1 = SymEngine::symbol("u1");

  ss->add_state(x1);
  ss->add_state(x2);
  ss->add_input(u1);

  std::string s;
  SymEngine::RCP<const SymEngine::Basic> res;

  s = "x2";
  res = SymEngine::parse(s);
  ss->add_f(res);

  s = "-sin(x1) - x2 + u1";
  res = SymEngine::parse(s);
  ss->add_f(res);

  s = "x2";
  res = SymEngine::parse(s);
  ss->add_g(res);

  SymEngine::DenseMatrix A = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});
  SymEngine::DenseMatrix B = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});

  SymEngine::DenseMatrix Co = SymEngine::DenseMatrix(1, 1,
                              {SymEngine::integer(1)});

  Controls::linearize(*ss);

  ss->get_A_matrix(A);
  ss->get_B_matrix(B);

  Controls::ctrb(A, B, Co);
  REQUIRE(Co == SymEngine::DenseMatrix(2, 2,
                {SymEngine::integer(0), SymEngine::integer(1),
                 SymEngine::integer(1), SymEngine::integer(-1)}));

  Controls::ctrb(*ss, Co);
  REQUIRE(Co == SymEngine::DenseMatrix(2, 2,
                {SymEngine::integer(0), SymEngine::integer(1),
                 SymEngine::integer(1), SymEngine::integer(-1)}));
}

TEST_CASE("Analysis: obsv", "[analysis]") {
  Controls::StateSpace *ss = new Controls::StateSpace();

  SymEngine::RCP<const SymEngine::Symbol> x1 = SymEngine::symbol("x1");
  SymEngine::RCP<const SymEngine::Symbol> x2 = SymEngine::symbol("x2");

  SymEngine::RCP<const SymEngine::Symbol> u1 = SymEngine::symbol("u1");

  ss->add_state(x1);
  ss->add_state(x2);
  ss->add_input(u1);

  std::string s;
  SymEngine::RCP<const SymEngine::Basic> res;

  s = "x2";
  res = SymEngine::parse(s);
  ss->add_f(res);

  s = "-sin(x1) - x2 + u1";
  res = SymEngine::parse(s);
  ss->add_f(res);

  s = "x2";
  res = SymEngine::parse(s);
  ss->add_g(res);

  SymEngine::DenseMatrix A = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});
  SymEngine::DenseMatrix C = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});

  SymEngine::DenseMatrix Ob = SymEngine::DenseMatrix(1, 1,
                              {SymEngine::integer(1)});

  Controls::linearize(*ss);

  ss->get_A_matrix(A);
  ss->get_C_matrix(C);

  Controls::obsv(A, C, Ob);
  REQUIRE(Ob == SymEngine::DenseMatrix(2, 2,
                {SymEngine::integer(0),  SymEngine::integer(1),
                 SymEngine::integer(-1), SymEngine::integer(-1)}));

  Controls::obsv(*ss, Ob);
  REQUIRE(Ob == SymEngine::DenseMatrix(2, 2,
                {SymEngine::integer(0),  SymEngine::integer(1),
                 SymEngine::integer(-1), SymEngine::integer(-1)}));
}
