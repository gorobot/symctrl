#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <type_traits>

#include <symctrl/math/functor/functor.hpp>
#include <symctrl/math/functor/lambda.hpp>
#include <symctrl/systems/functor/functor.hpp>

TEST_CASE("Functor: Lambda", "[functor]") {
  {
    auto f = Controls::Math::lambda_functor(
      [](const double i, const double j) -> double {
        return i*2 + j;
      }
    );

    REQUIRE(f(1, 2) == 4);
  }

  {
    double result;
    auto f = Controls::Math::lambda_functor(
      [&](const double i, const double j) {
        result = i*2 + j;
      }
    );

    f(1, 2);
    REQUIRE(result == 4);
  }

  {
    double coeff = 2;
    auto f = Controls::Math::lambda_functor(
      [=](const double i, const double j) -> double {
        return i*coeff + j;
      }
    );

    REQUIRE(f(1, 2) == 4);
  }
}

TEST_CASE("Functor: Control Policy", "[function]") {
  std::vector<double> a = {1, 2};

  {
    auto f = Controls::Math::lambda_functor(
      [](const std::vector<double> &state) -> std::vector<double> {
        std::vector<double> next_input(state);

        for(size_t i = 0; i < next_input.size(); i++) {
          next_input[i]++;
        }

        return next_input;
      }
    );

    std::vector<double> v = f(a);
    REQUIRE(v[0] == 2);
    REQUIRE(v[1] == 3);

    REQUIRE(Controls::is_a_control_policy(f));
  }

  {
    auto f = Controls::control_policy(
      [](const std::vector<double> &state) -> std::vector<double> {
         std::vector<double> next_input(state);

        for(size_t i = 0; i < next_input.size(); i++) {
          next_input[i]++;
        }

        return next_input;
      }
    );

    std::vector<double> v = (*f)(a);
    REQUIRE(v[0] == 2);
    REQUIRE(v[1] == 3);

    REQUIRE(Controls::is_a_control_policy(*f));
  }
}

TEST_CASE("Functor: Cost Function", "[function]") {
  std::vector<double> a = {1, 2};
  std::vector<double> b = {1, 2};

  {
    auto f = Controls::Math::lambda_functor(
      [](const std::vector<double> &state,
         const std::vector<double> &input) -> double {
          return 1;
        }
    );

    REQUIRE(Controls::is_a_cost_function(f));
  }

  {
    auto f = Controls::cost_function(
      [](const std::vector<double> &state,
         const std::vector<double> &input) -> double {
          return 1;
        }
    );

    REQUIRE(Controls::is_a_cost_function(*f));
  }
}

TEST_CASE("Functor: Transition Function", "[function]") {
  std::vector<double> a = {1, 2};
  std::vector<double> b = {1, 2};

  {
    auto f = Controls::Math::lambda_functor(
      [](const std::vector<double> &state,
         const std::vector<double> &input) -> std::vector<double> {
        std::vector<double> next_state(state);

        for(size_t i = 0; i < next_state.size(); i++) {
          next_state[i] += input[i];
        }

        return next_state;
      }
    );

    std::vector<double> v = f(a, b);

    REQUIRE(v[0] == 2);
    REQUIRE(v[1] == 4);
    REQUIRE(Controls::is_a_transition_function(f));
  }

  {
    auto f = Controls::transition_function(
      [](const std::vector<double> &state,
         const std::vector<double> &input) -> std::vector<double> {
        std::vector<double> next_state(state);

        for(size_t i = 0; i < next_state.size(); i++) {
          next_state[i] += input[i];
        }

        return next_state;
      }
    );

    std::vector<double> v = (*f)(a, b);

    REQUIRE(v[0] == 2);
    REQUIRE(v[1] == 4);
    REQUIRE(Controls::is_a_transition_function(*f));
  }
}
