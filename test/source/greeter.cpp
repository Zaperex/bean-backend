#include <doctest/doctest.h>  // for ResultBuilder, CHECK, TestCase, TEST_CASE

#include <beanbackend/greeter.hpp>  // for Greeter, LanguageCode
#include <string>                   // for basic_string, operator==, allocator

TEST_CASE("Greeter")
{
  using namespace greeter;

  const Greeter greeter("Tests");
  CHECK(greeter.greet(LanguageCode::EN) == "Hello bob, Tests!");
  CHECK(greeter.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK(greeter.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK(greeter.greet(LanguageCode::FR) == "Bonjour Tests!");
}
