#pragma once

#include <oatpp-1.3.0/oatpp/oatpp/core/Types.hpp>
#include <oatpp-1.3.0/oatpp/oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace bean
{
  class Budget : public oatpp::DTO
  {
  }
}  // namespace bean

#include OATPP_CODEGEN_END(DTO)
