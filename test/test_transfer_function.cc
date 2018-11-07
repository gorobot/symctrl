#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/transfer_function.hpp>

TEST_CASE("Transfer function: var", "[transferfunction]") {
  Controls::TransferFunction *tf1 = new Controls::TransferFunction();

  SymEngine::RCP<const SymEngine::Symbol> s = SymEngine::symbol("s");

  tf1->set_var(s);
  REQUIRE(s->__eq__(*(tf1->get_var())));

  Controls::TransferFunction *tf2 = new Controls::TransferFunction(s);

  REQUIRE(s->__eq__(*(tf2->get_var())));
}

TEST_CASE("Transfer function: num/den", "[transferfunction]") {
  SymEngine::RCP<const SymEngine::Symbol> s = SymEngine::symbol("s");

  Controls::TransferFunction *tf = new Controls::TransferFunction(s);

  std::string s1;
  std::string s2;
  std::string s3;
  std::string s4;
  SymEngine::RCP<const SymEngine::Basic> res1;
  SymEngine::RCP<const SymEngine::Basic> res2;
  SymEngine::RCP<const SymEngine::Basic> res3;
  SymEngine::RCP<const SymEngine::Basic> res4;

  s1 = "1 + s";
  res1 = SymEngine::parse(s1);
  tf->add_num(res1);
  REQUIRE(res1->__eq__(*(tf->get_num(0))));
  REQUIRE(SymEngine::has_symbol(*(tf->get_num(0)), *s));

  s2 = "1 - s";
  res2 = SymEngine::parse(s2);
  tf->add_den(res2);
  REQUIRE(res1->__eq__(*(tf->get_num(0))));
  REQUIRE(res2->__eq__(*(tf->get_den(0))));
  REQUIRE(SymEngine::has_symbol(*(tf->get_num(0)), *s));
  REQUIRE(SymEngine::has_symbol(*(tf->get_den(0)), *s));

  s2 = "1 - s^2";
  res2 = SymEngine::parse(s2);
  tf->set_den(0, res2);
  REQUIRE(res1->__eq__(*(tf->get_num(0))));
  REQUIRE(res2->__eq__(*(tf->get_den(0))));
  REQUIRE(SymEngine::has_symbol(*(tf->get_num(0)), *s));
  REQUIRE(SymEngine::has_symbol(*(tf->get_den(0)), *s));

  s3 = "s^2";
  res3 = SymEngine::parse(s3);
  tf->add_num(res3);
  REQUIRE(res1->__eq__(*(tf->get_num(0))));
  REQUIRE(res2->__eq__(*(tf->get_den(0))));
  REQUIRE(res3->__eq__(*(tf->get_num(1))));
  REQUIRE(SymEngine::has_symbol(*(tf->get_num(0)), *s));
  REQUIRE(SymEngine::has_symbol(*(tf->get_den(0)), *s));
  REQUIRE(SymEngine::has_symbol(*(tf->get_num(1)), *s));

  s4 = "s";
  res4 = SymEngine::parse(s4);
  tf->add_den(res4);
  REQUIRE(res1->__eq__(*(tf->get_num(0))));
  REQUIRE(res2->__eq__(*(tf->get_den(0))));
  REQUIRE(res3->__eq__(*(tf->get_num(1))));
  REQUIRE(res4->__eq__(*(tf->get_den(1))));
  REQUIRE(SymEngine::has_symbol(*(tf->get_num(0)), *s));
  REQUIRE(SymEngine::has_symbol(*(tf->get_den(0)), *s));
  REQUIRE(SymEngine::has_symbol(*(tf->get_num(1)), *s));
  REQUIRE(SymEngine::has_symbol(*(tf->get_den(1)), *s));

  size_t n;

  n = tf->get_num_nums();
  REQUIRE(n == 2);

  n = tf->get_num_dens();
  REQUIRE(n == 2);
}
