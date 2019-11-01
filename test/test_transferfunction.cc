#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/basic.h>
#include <symengine/symbol.h>

#include <symctrl/systems/transferfunction.hpp>
#include <symctrl/shims/equal.hpp>
#include <symctrl/shims/symbolic.hpp>
#include <symctrl/shims/parse.hpp>

using Controls::equal;
using Controls::TransferFunction;
using Controls::parse;
using Controls::symbolic_t;
using Controls::symbolic_symbol_t;

using SymEngine::symbol;

TEST_CASE("TransferFunction: Assignment", "[transferfunction]") {
  symbolic_symbol_t s = symbol("s");

  {
    TransferFunction tf(s, parse("1"), parse("s"));
    REQUIRE(equal(tf.var(), s));
    REQUIRE(equal(tf.numerator(), parse("1")));
    REQUIRE(equal(tf.denominator(), parse("s")));
  }

  {
    TransferFunction tf(s, parse("s"), parse("s^2"));
    REQUIRE(equal(tf.var(), s));
    REQUIRE(equal(tf.numerator(), parse("s")));
    REQUIRE(equal(tf.denominator(), parse("s^2")));

    // When the transfer function is converted to a symbolic variable, it
    // performs pole/zero cancellations automatically.
    symbolic_t R = tf;
    REQUIRE(equal(R, parse("1/s")));
  }
}

TEST_CASE("TransferFunction: Series", "[transferfunction]") {
  symbolic_symbol_t s = symbol("s");

  {
    TransferFunction H1(s, parse("1"), parse("s"));
    TransferFunction H2(s, parse("2"), parse("s"));

    TransferFunction H = H1 * H2;

    REQUIRE(equal(H.numerator(), parse("3*s")));
    REQUIRE(equal(H.denominator(), parse("s^2")));
  }

  {
    TransferFunction H1(s, parse("2"), parse("s^2 + 3*s"));
    TransferFunction H2(s, parse("5"), parse("s + 5"));

    TransferFunction H = H1 * H2;

    REQUIRE(equal(H.numerator(), parse("2*(5 + s) + 5*(3*s + s^2)")));
    REQUIRE(equal(H.denominator(), parse("(5 + s)*(3*s + s^2)")));
  }
}

TEST_CASE("TransferFunction: Parallel", "[transferfunction]") {
  symbolic_symbol_t s = symbol("s");

  {
    TransferFunction H1(s, parse("1"), parse("s"));
    TransferFunction H2(s, parse("2"), parse("s"));

    TransferFunction H = H1 + H2;

    REQUIRE(equal(H.numerator(), parse("2")));
    REQUIRE(equal(H.denominator(), parse("s^2")));
  }

  {
    TransferFunction H1(s, parse("2"), parse("s^2 + 3*s"));
    TransferFunction H2(s, parse("5"), parse("s + 5"));

    TransferFunction H = H1 + H2;

    REQUIRE(equal(H.numerator(), parse("10")));
    REQUIRE(equal(H.denominator(), parse("(5 + s)*(3*s + s^2)")));
  }
}
