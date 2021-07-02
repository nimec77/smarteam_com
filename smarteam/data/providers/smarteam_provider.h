//
// Created by nim on 30.06.2021.
//
#ifndef SMARTEAM_COM_SMARTEAM_PROVIDER_H
#define SMARTEAM_COM_SMARTEAM_PROVIDER_H

#include <iostream>
#include <sstream>
#include <windows.h>
#include <constants.h>
#include <data/data_helper.h>


class SmarteamProvider {
public:
    SmarteamProvider();

    virtual ~SmarteamProvider();

    virtual IDispatch* get_engine();

private:
    IDispatch* smarteam_app{};
};


#endif //SMARTEAM_COM_SMARTEAM_PROVIDER_H
