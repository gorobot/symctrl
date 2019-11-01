#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symengine/cwrapper.h>
#include <symctrl/c_wrapper.hpp>

#include <symctrl/math/random.hpp>
#include <symctrl/shims/symbolic.hpp>

using Controls::symbolic_t;
using Controls::symbolic_rv_t;

using SymEngine::add;
using SymEngine::Add;
using SymEngine::Basic;
using SymEngine::RCP;
using SymEngine::symbol;
using SymEngine::Symbol;

TEST_CASE("Random Variable", "[randomvariable]") {
  std::random_device gen;
  Controls::Math::normal_distribution<> d{5,2};

  symbolic_rv_t X = Controls::Math::random_variable("X", &d);

  REQUIRE(Controls::Math::is_random_variable(*X));
  REQUIRE(X->get_name() == "X");

  symbolic_t y = symbol("y");

  REQUIRE(not Controls::Math::is_random_variable(*y));

  // std::cout << d(gen) << '\n';
  // std::cout << X->sample(gen) << '\n';
  // for(size_t i = 0; i < 10000; i++) {
  //   X->sample(gen);
  // }
}

TEST_CASE("Random Variable: add", "[randomvariable]") {
  std::random_device gen;
  Controls::Math::normal_distribution<> d{5,2};

  symbolic_rv_t X = Controls::Math::random_variable("X", &d);

  symbolic_t y = symbol("y");

  symbolic_t r = add(add(X, y), y);

  std::string s;
  symbolic_t res;

  s = "X + 2*y";
  res = SymEngine::parse(s);

  REQUIRE(res->__eq__(*r));
  REQUIRE(SymEngine::has_symbol(*r, *X));

  RCP<const Add> ar = SymEngine::rcp_static_cast<const Add>(r);
  const SymEngine::umap_basic_num &add_map = ar->get_dict();
  auto search = add_map.find(X);
  REQUIRE(search != add_map.end());
  REQUIRE(eq(*search->first, *X));
  REQUIRE(Controls::Math::is_random_variable(*search->first));
}

// TEST_CASE("Random Variable: C Wrapper", "[randomvariable]") {
//   auto d = random_number_distribution_new();
//   normal_distribution_set(d, 0, 1);
//
//   auto g = random_device_new();
//   random_device_init(g);
//
//   auto s = random_variable_new();
//   random_variable_set(s, "x", d);
//
//   // std::cout << *(s->m) << '\n';
//
//   double r = random_variable_sample(s, g);
//   // std::cout << "TEST SAMPLE" << '\n';
//   // std::cout << random_variable_sample(s, g) << '\n';
//
//   random_device_free(g);
//   random_variable_free(s);
//   random_number_distribution_free(d);
//
//   // REQUIRE(0 == 1);
// }
