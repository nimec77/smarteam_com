#include <iostream>
#include <data/providers/database_provider.h>
#include <data/providers/smarteam_provider.h>
#include <data/providers/engine_provider.h>
#include <data/providers/session_provider.h>

int main() {
  std::cout << "SmarTeam COM start" << std::endl;
  SmarteamProvider smarteam_provider;
  const auto engine = smarteam_provider.get_engine();
  EngineProvider engine_provider(engine);
  auto session_app = engine_provider.create_session(L"CppSmarTeamSession", L"SmTeam32");
  data_helper::get_dispatch_methods(session_app);
  auto database_app = engine_provider.get_database(0);
  DatabaseProvider database_provider(database_app);
  auto database_alias = database_provider.get_alias();
  std::cout << "Alias:" << helper::utf16_to_utf8(database_alias) << std::endl;
  auto database_password = database_provider.get_password();
  SessionProvider session_provider(session_app);
  std::cout << "Password:" << helper::utf16_to_utf8(database_password) << std::endl;
  session_provider.open_database_connection(database_alias, database_password, true);
  std::cout << "SmarTeam COM end" << std::endl;
  return 0;
}
