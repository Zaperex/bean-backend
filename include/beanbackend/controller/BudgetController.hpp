#pragma once

#include <beanbackend/dto/budget.hpp>
#include <memory>
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/web/server/HttpRequestHandler.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

namespace bean::server::controller
{
  /// @cond DOC_IGNORE
#include OATPP_CODEGEN_BEGIN(ApiController)
  /// @endcond
  /**
   * Controller for budget related endpoints.
   */
  class BudgetController : public oatpp::web::server::api::ApiController
  {
   public:
    /**
     * Constructor.
     */
    explicit BudgetController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {
    }
    /**
     * Budgets endpoint information, used for swagger.
     */
    ENDPOINT_INFO(getBudgets)
    {
      info->summary = "Get all budgets";
      info->addResponse<Object<dto::Budget>>(Status::CODE_200, "application/json");
    }
    /**
     * Specifying the /budgets endpoint.
     */
    ENDPOINT("GET", "/budgets", getBudgets)
    {
      const auto budget = dto::Budget::createShared("restaurants", 42.34);

      return createDtoResponse(Status::CODE_200, budget);
    }
  };
}  // namespace bean::server::controller
