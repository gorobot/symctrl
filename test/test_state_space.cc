#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/state_space.hpp>

TEST_CASE("State space: states", "[statespace]") {
  Controls::StateSpace *ss = new Controls::StateSpace();

  SymEngine::RCP<const SymEngine::Symbol> x1 = SymEngine::symbol("x1");
  SymEngine::RCP<const SymEngine::Symbol> x2 = SymEngine::symbol("x2");
  SymEngine::RCP<const SymEngine::Symbol> x3 = SymEngine::symbol("x3");

  ss->add_state(x1);
  REQUIRE(x1->__eq__(*(ss->get_state(0))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_state(0)), *x1));

  ss->add_state(x2);
  REQUIRE(x1->__eq__(*(ss->get_state(0))));
  REQUIRE(x2->__eq__(*(ss->get_state(1))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_state(1)), *x2));
  REQUIRE(not(SymEngine::has_symbol(*(ss->get_state(1)), *x1)));

  ss->set_state(1, x3);
  REQUIRE(x3->__eq__(*(ss->get_state(1))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_state(1)), *x3));

  size_t n = ss->get_num_states();
  REQUIRE(n == 2);
}

TEST_CASE("State space: inputs", "[statespace]") {
  Controls::StateSpace *ss = new Controls::StateSpace();

  SymEngine::RCP<const SymEngine::Symbol> u1 = SymEngine::symbol("u1");
  SymEngine::RCP<const SymEngine::Symbol> u2 = SymEngine::symbol("u2");
  SymEngine::RCP<const SymEngine::Symbol> u3 = SymEngine::symbol("u3");

  ss->add_input(u1);
  REQUIRE(u1->__eq__(*(ss->get_input(0))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_input(0)), *u1));

  ss->add_input(u2);
  REQUIRE(u1->__eq__(*(ss->get_input(0))));
  REQUIRE(u2->__eq__(*(ss->get_input(1))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_input(1)), *u2));
  REQUIRE(not(SymEngine::has_symbol(*(ss->get_input(1)), *u1)));

  ss->set_input(1, u3);
  REQUIRE(u3->__eq__(*(ss->get_input(1))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_input(1)), *u3));

  size_t n = ss->get_num_inputs();
  REQUIRE(n == 2);
}

TEST_CASE("State space: state functions", "[statespace]") {
  Controls::StateSpace *ss = new Controls::StateSpace();

  SymEngine::RCP<const SymEngine::Symbol> x1 = SymEngine::symbol("x1");
  SymEngine::RCP<const SymEngine::Symbol> x2 = SymEngine::symbol("x2");

  SymEngine::RCP<const SymEngine::Symbol> u1 = SymEngine::symbol("u1");

  std::string s1;
  std::string s2;
  SymEngine::RCP<const SymEngine::Basic> res1;
  SymEngine::RCP<const SymEngine::Basic> res2;

  s1 = "x2";
  res1 = SymEngine::parse(s1);
  ss->add_f(res1);
  REQUIRE(res1->__eq__(*(ss->get_f(0))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_f(0)), *x2));

  s2 = "-sin(x1) + x2 + u1";
  res2 = SymEngine::parse(s2);
  ss->add_f(res2);
  REQUIRE(res1->__eq__(*(ss->get_f(0))));
  REQUIRE(res2->__eq__(*(ss->get_f(1))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_f(1)), *x1));
  REQUIRE(SymEngine::has_symbol(*(ss->get_f(1)), *x2));
  REQUIRE(SymEngine::has_symbol(*(ss->get_f(1)), *u1));

  s2 = "-sin(x1) - x2 + u1";
  res2 = SymEngine::parse(s2);
  ss->set_f(1, res2);
  REQUIRE(res2->__eq__(*(ss->get_f(1))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_f(1)), *x1));
  REQUIRE(SymEngine::has_symbol(*(ss->get_f(1)), *x2));
  REQUIRE(SymEngine::has_symbol(*(ss->get_f(1)), *u1));

  size_t n = ss->get_num_f();
  REQUIRE(n == 2);
}

TEST_CASE("State space: output functions", "[statespace]") {
  Controls::StateSpace *ss = new Controls::StateSpace();

  SymEngine::RCP<const SymEngine::Symbol> x1 = SymEngine::symbol("x1");
  SymEngine::RCP<const SymEngine::Symbol> x2 = SymEngine::symbol("x2");

  SymEngine::RCP<const SymEngine::Symbol> u1 = SymEngine::symbol("u1");

  std::string s1;
  std::string s2;
  SymEngine::RCP<const SymEngine::Basic> res1;
  SymEngine::RCP<const SymEngine::Basic> res2;

  s1 = "x1";
  res1 = SymEngine::parse(s1);
  ss->add_g(res1);
  REQUIRE(res1->__eq__(*(ss->get_g(0))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_g(0)), *x1));

  s2 = "x1 + x2";
  res2 = SymEngine::parse(s2);
  ss->add_g(res2);
  REQUIRE(res1->__eq__(*(ss->get_g(0))));
  REQUIRE(res2->__eq__(*(ss->get_g(1))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_g(1)), *x1));
  REQUIRE(SymEngine::has_symbol(*(ss->get_g(1)), *x2));

  s2 = "x1 + x2 + u1";
  res2 = SymEngine::parse(s2);
  ss->set_g(1, res2);
  REQUIRE(res2->__eq__(*(ss->get_g(1))));
  REQUIRE(SymEngine::has_symbol(*(ss->get_g(1)), *x1));
  REQUIRE(SymEngine::has_symbol(*(ss->get_g(1)), *x2));
  REQUIRE(SymEngine::has_symbol(*(ss->get_g(1)), *u1));

  size_t n = ss->get_num_g();
  REQUIRE(n == 2);
}

TEST_CASE("State space: A matrix", "[statespace]") {
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

  SymEngine::DenseMatrix A = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});

  s = "-cos(x1)";
  res = SymEngine::parse(s);
  ss->get_A_matrix(A);
  REQUIRE(A == SymEngine::DenseMatrix(2, 2,
               {SymEngine::integer(0), SymEngine::integer(1),
                res,                   SymEngine::integer(-1)}));
}

TEST_CASE("State space: B matrix", "[statespace]") {
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

  SymEngine::DenseMatrix B = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});

  ss->get_B_matrix(B);
  REQUIRE(B == SymEngine::DenseMatrix(2, 1,
               {SymEngine::integer(0), SymEngine::integer(1)}));
}

TEST_CASE("State space: C matrix", "[statespace]") {
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
  ss->add_g(res);

  SymEngine::DenseMatrix C = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});

  ss->get_C_matrix(C);
  REQUIRE(C == SymEngine::DenseMatrix(1, 2,
               {SymEngine::integer(0), SymEngine::integer(1)}));
}

TEST_CASE("State space: D matrix", "[statespace]") {
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
  ss->add_g(res);

  SymEngine::DenseMatrix D = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});

  ss->get_D_matrix(D);
  REQUIRE(D == SymEngine::DenseMatrix(1, 1,
               {SymEngine::integer(0)}));
}

TEST_CASE("State space: linearize", "[statespace]") {
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

  SymEngine::DenseMatrix A = SymEngine::DenseMatrix(1, 1,
                             {SymEngine::integer(1)});

  s = "-cos(x1)";
  res = SymEngine::parse(s);
  ss->get_A_matrix(A);
  REQUIRE(A == SymEngine::DenseMatrix(2, 2,
               {SymEngine::integer(0), SymEngine::integer(1),
                res,                   SymEngine::integer(-1)}));

  Controls::linearize(*ss);

  ss->get_A_matrix(A);
  REQUIRE(A == SymEngine::DenseMatrix(2, 2,
               {SymEngine::integer(0),  SymEngine::integer(1),
                SymEngine::integer(-1), SymEngine::integer(-1)}));

}
