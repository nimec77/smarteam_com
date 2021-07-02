//
// Created by nim on 30.06.2021.
//
#ifndef SMARTEAM_COM_SMARTEAM_PROVIDER_H
#define SMARTEAM_COM_SMARTEAM_PROVIDER_H

#include <iostream>
#include <sstream>
#include <windows.h>


class SmarteamProvider {
public:
    SmarteamProvider();

    virtual ~SmarteamProvider();

    constexpr static auto const kProgId = L"SmarTeam.Application";

    virtual IDispatch* get_engine();

private:
    IDispatch* smarteam_app{};
};


#endif //SMARTEAM_COM_SMARTEAM_PROVIDER_H
