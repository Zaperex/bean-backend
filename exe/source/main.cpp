#include <beanbackend/AppComponent.hpp>
#include <beanbackend/controller/BudgetController.hpp>
#include <beanbackend/controller/greeter_controller.hpp>
#include <memory>
#include <oatpp-swagger/Controller.hpp>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/network/Address.hpp>
#include <oatpp/network/Server.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/web/server/api/Endpoint.hpp>

auto run()
{
  /* Register Components in scope of run() method */
  bean::server::AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  oatpp::web::server::api::Endpoints docEndpoints;

  router->route("GET", greeter::GreeterHandler::PATH_PATTERN, std::make_shared<greeter::GreeterHandler>());
  docEndpoints.append(router->addController(std::make_shared<bean::server::controller::BudgetController>())->getEndpoints());
  router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  oatpp::network::Server server{ connectionProvider, connectionHandler };

  OATPP_LOGI("BEANSERVER", "Server running on port %s", connectionProvider->getProperty("port").std_str().c_str());

  server.run();
}

auto main(int /*argc*/, char** /*argv*/) -> int
{
  oatpp::base::Environment::init();

  run();

  oatpp::base::Environment::destroy();
}
