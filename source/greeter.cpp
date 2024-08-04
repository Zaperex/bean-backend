#include <beanbackend/greeter.h>  // for Greeter, LanguageCode
#include <fmt/format.h>           // for format

#include <string>   // for basic_string, string
#include <utility>  // for move

#include "fmt/base.h"  // for format_string

using namespace greeter;

Greeter::Greeter(std::string _name) : name(std::move(_name))
{
}

std::string Greeter::greet(LanguageCode lang) const
{
  switch (lang)
  {
    default:
    case LanguageCode::EN: return fmt::format("Hello, {}!", name);
    case LanguageCode::DE: return fmt::format("Hallo {}!", name);
    case LanguageCode::ES: return fmt::format("¡Hola {}!", name);
    case LanguageCode::FR: return fmt::format("Bonjour {}!", name);
  }
}
