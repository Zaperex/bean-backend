#include <beanbackend/http_handlers/greeter_handler.h>

#include <memory>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/network/Address.hpp>
#include <oatpp/network/Server.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>

auto run()
{
  auto router = oatpp::web::server::HttpRouter::createShared();
  router->route("GET", greeter::GreeterHandler::ENDPOINT, std::make_shared<greeter::GreeterHandler>());

  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
  constexpr uint16_t IP_PORT = 1234;
  auto connectionProvider =
      oatpp::network::tcp::server::ConnectionProvider::createShared({ "localhost", IP_PORT, oatpp::network::Address::IP_4 });

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
