#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <chrono>

#include <symengine/visitor.h>
#include <symengine/parser.h>

// #include <symctrl/ode/ode.hpp>
// #include <symctrl/math/random/random_variable.hpp>
#include <symctrl/ode/ode.hpp>
#include <symctrl/shims/symbolic.hpp>
#include <symctrl/shims/parse.hpp>

using Controls::parse;
using Controls::StateSpace;
using Controls::symbolic_symbol_t;

using SymEngine::Basic;
using SymEngine::RCP;
using SymEngine::symbol;
using SymEngine::Symbol;

TEST_CASE("ODE: Options", "[ode]") {
  Controls::ode_options options;

  REQUIRE(options.step_size() == 0.01);
  REQUIRE(options.t_begin() == 0);
  REQUIRE(options.t_end() == 10);
}

TEST_CASE("ODE: Euler", "[ODE]") {
  symbolic_symbol_t x = symbol("x");

  StateSpace sys;

  sys.state_variables = {x};
  sys.state_equations = {parse("2*x + 1")};

  std::vector<double> x0 = {1};
  std::vector<double> t_result;
  std::vector<double> x_result;
  Controls::ode_options options;
  options.t_begin(0);
  options.t_end(1);
  options.step_size(0.001);

  Controls::ode_euler(sys, x0, t_result, x_result, options);

  REQUIRE(::fabs(x_result.front() - 1.0) < 1e-9);
  REQUIRE(::fabs(x_result.back() - 10.5614685855) < 1e-9);

  REQUIRE(t_result.size() == 1001);
  REQUIRE(x_result.size() == 1001);
}

TEST_CASE("ODE: Euler Pendulum", "[ODE]") {
  symbolic_symbol_t x1 = symbol("x1");
  symbolic_symbol_t x2 = symbol("x2");

  StateSpace sys;

  sys.state_variables = {x1, x2};
  sys.state_equations = {parse("x2"), parse("-sin(x1) - x2")};

  std::vector<double> x0 = {4, 0};
  std::vector<double> t_result;
  std::vector<double> x_result;
  Controls::ode_options options;
  options.t_begin(0);
  options.t_end(20);
  options.step_size(0.001);

  Controls::ode_euler(sys, x0, t_result, x_result, options);

  REQUIRE(::fabs(x_result.at(0) - 4.00) < 1e-3);
  REQUIRE(::fabs(x_result.at(1) - 0.00) < 1e-3);
  REQUIRE(::fabs(x_result.at(40000) - 6.283) < 1e-3);
  REQUIRE(::fabs(x_result.at(40001) - 0.000) < 1e-3);

  REQUIRE(t_result.size() == 20001);
  REQUIRE(x_result.size() == 40002);
}

TEST_CASE("ODE: Euler Pendulum Profile", "[ODE]") {
  symbolic_symbol_t x1 = symbol("x1");
  symbolic_symbol_t x2 = symbol("x2");

  StateSpace sys;

  sys.state_variables = {x1, x2};
  sys.state_equations = {parse("x2"), parse("-sin(x1) - x2")};

  std::vector<double> x0 = {4, 0};
  std::vector<double> t_result;
  std::vector<double> x_result;
  Controls::ode_options options;
  options.t_begin(0);
  options.t_end(20);
  options.step_size(0.001);

  using nano = std::chrono::nanoseconds;
  auto start = std::chrono::high_resolution_clock::now();

  Controls::ode_euler(sys, x0, t_result, x_result, options);

  auto finish = std::chrono::high_resolution_clock::now();
  std::cout << "duration ode euler: "
            << std::chrono::duration_cast<nano>(finish - start).count()
            << '\n';
}
//
// TEST_CASE("ODE: Random Variable", "[ODE]") {
//   Controls::StateSpace *ss = new Controls::StateSpace();
//
//   RCP<const Symbol> x1 = symbol("x1");
//   RCP<const Symbol> x2 = symbol("x2");
//
//   Controls::Math::normal_distribution<> d{5,2};
//   RCP<const Controls::Math::RandomVariable> Z;
//   Z = Controls::Math::random_variable("Z", &d);
//
//   std::string s;
//   RCP<const Basic> res;
//
//   ss->add_state(x1);
//   ss->add_state(x2);
//
//   s = "x2";
//   res = SymEngine::parse(s);
//   ss->add_f(res);
//
//   s = "-sin(x1) - x2";
//   res = SymEngine::parse(s);
//   res = SymEngine::add(res, Z);
//   ss->add_f(res);
//
//   std::vector<double> t_span = {0, 20};
//   std::vector<double> x0 = {4, 0};
//   std::vector<double> t_result;
//   std::vector<double> x_result;
//   Controls::OdeOptions *options = new Controls::OdeOptions();
//
//   Controls::ode_euler(*ss, t_span, x0, t_result, x_result, *options);
// }
