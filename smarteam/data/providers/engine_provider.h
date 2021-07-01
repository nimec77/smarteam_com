//
// Created by nim on 30.06.2021.
//

#ifndef SMARTEAM_COM_ENGINE_PROVIDER_H
#define SMARTEAM_COM_ENGINE_PROVIDER_H

#include <iostream>
#include <sstream>
#include <windows.h>


class EngineProvider {
public:
    explicit EngineProvider(IDispatch *engineApp);

    virtual ~EngineProvider();

    IDispatch *create_session(const wchar_t* application_name, const wchar_t* configuration_name);

private:
    IDispatch *engine_app;
};


#endif //SMARTEAM_COM_ENGINE_PROVIDER_H
