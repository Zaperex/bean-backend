#pragma once

#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <utility>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace bean::dto
{
  /**
   * A class representing a budget.
   */
  class Budget : public oatpp::DTO
  {
    DTO_INIT(Budget, DTO);

   private:
    DTO_FIELD(String, category);
    DTO_FIELD(Float64, price);

   public:
    /**
     * Construct a budget.
     * @param category the type of budget
     * @param price the total allocation for the budget.
     */
    Budget(String category, Float64 price) : category(std::move(category)), price(std::move(price))
    {
    }
    Budget() = default;
  };
}  // namespace bean::dto

#include OATPP_CODEGEN_END(DTO)
