#pragma once

#include <beanbackend/greeter.hpp>
#include <memory>
#include <oatpp/web/server/HttpRequestHandler.hpp>

namespace greeter
{
  /**
   * Handles the "/greet" endpoint.
   */
  class GreeterHandler : public oatpp::web::server::HttpRequestHandler
  {
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override
    {
      // TODO: This should NOT be inside the header file!
      auto greeter = Greeter{ request->getQueryParameter("name").getValue("noname") };
      return ResponseFactory::createResponse(Status::CODE_200, greeter.greet(LanguageCode::FR));
    }

   public:
    /**
     * The endpoint.
     */
    static constexpr std::string PATH_PATTERN{ "/greet" };
  };
}  // namespace greeter
