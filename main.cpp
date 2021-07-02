#include <iostream>
#include <data/providers/database_provider.h>
#include <data/providers/smarteam_provider.h>
#include <data/providers/engine_provider.h>
#include <data/providers/session_provider.h>
#include <constants.h>

int main() {
  system("chcp 65001");
  std::cout << "SmarTeam COM start" << std::endl;
  CoInitialize(nullptr);
  SmarteamProvider smarteam_provider;

  const auto engine = smarteam_provider.get_engine();
  EngineProvider engine_provider(engine);

  auto application_name = _bstr_t(kApplicationName);
  auto configuration_name = _bstr_t(kConfigurationName);
  auto session_app = engine_provider.create_session(application_name, configuration_name);
  auto database_app = engine_provider.get_database(0);

  DatabaseProvider database_provider(database_app);
  auto database_alias = database_provider.get_alias();
  std::cout << "Alias:" << helper::utf16_to_utf8(database_alias) << std::endl;
  auto database_password = database_provider.get_password();
  std::cout << "Password:" << helper::utf16_to_utf8(database_password) << std::endl;

  SessionProvider session_provider(session_app);
  session_provider.open_database_connection(database_alias, database_password, true);
  std::cout << "Database connected" << std::endl;

  auto user_name = _bstr_t(kUserName);
  auto password = _bstr_t(kUserPassword);
  auto result_bool = session_provider.user_login(user_name, password);
  std::cout << "User login: " << std::boolalpha << result_bool << std::endl;

  result_bool = session_provider.user_logged_on();
  std::cout << "User logged on: " << std::boolalpha << result_bool << std::endl;

  std::cout << "SmarTeam COM end" << std::endl;
  return 0;
}
