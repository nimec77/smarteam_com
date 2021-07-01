#include <iostream>
#include "smarteam/data/providers/smarteam_provider.h"
#include "smarteam/data/providers/engine_provider.h"

int main() {
    std::cout << "SmarTeam COM start" << std::endl;
    SmarteamProvider smarteam_provider;
    const auto engine = smarteam_provider.get_engine();
    EngineProvider engine_provider(engine);
    auto session = engine_provider.create_session(L"CppSmarTeamSession", L"SmTeam32");
    std::cout << "SmarTeam COM end" << std::endl;
    return 0;
}
