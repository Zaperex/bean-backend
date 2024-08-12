#pragma once

#include <cstdint>
#include <oatpp-swagger/Model.hpp>
#include <oatpp-swagger/Resources.hpp>

#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

namespace bean::server
{
  /**
   *  Class which creates and holds Application components and registers components in oatpp::base::Environment
   *  Order of components initialization is from top to bottom
   *  @note This class contains many dependency injection constructs from @c oatpp. They are defined
   *  using complex macros that doxygen cannot handle. Please refer to the source code for details.
   */
  class AppComponent
  {
   public:
    /**
     * Port that the server runs on.
     */
    constexpr static std::uint16_t PORT = 1234;
    /// @cond DOC_IGNORE
    /// Doxygen can't properly handle these macros.
    /**
     *  Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)
    (
        []
        {
          return oatpp::network::tcp::server::ConnectionProvider::createShared(
              { "localhost", PORT, oatpp::network::Address::IP_4 });
        }());

    /**
     *  Create Router component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
    ([] { return oatpp::web::server::HttpRouter::createShared(); }());

    /**
     *  Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)
    (
        []
        {
          OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);  // get Router component
          return oatpp::web::server::HttpConnectionHandler::createShared(router);
        }());

    /**
     *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
    ([] { return oatpp::parser::json::mapping::ObjectMapper::createShared(); }());

    /**
     * General API docs info
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)
    (
        []
        {
          oatpp::swagger::DocumentInfo::Builder builder;

          builder.setTitle("BEAN server")
              .setDescription("CRUD API Example project with swagger docs")
              .setVersion("1.0")
              .setContactName("BEAN org")
              .setContactUrl("bean@beans.bean")

              .setLicenseName("Apache License, Version 2.0")
              .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")

              .addServer("http://localhost:1234", "server on localhost");

          return builder.build();
        }());

    /**
     *  Swagger-Ui Resources
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)
    ([] { return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH); }());

    /// @endcond
  };
}  // namespace bean::server
