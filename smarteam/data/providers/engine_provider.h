//
// Created by nim on 30.06.2021.
//

#ifndef SMARTEAM_COM_ENGINE_PROVIDER_H
#define SMARTEAM_COM_ENGINE_PROVIDER_H

#include <iostream>
#include <sstream>
#include <windows.h>
#include <data/data_helper.h>
#include <constants.h>

class EngineProvider {
public:
    explicit EngineProvider(IDispatch *engine_app);

    virtual ~EngineProvider();

    virtual IDispatch *create_session(_bstr_t& application_name, _bstr_t& configuration_name);

    virtual IDispatch *get_database(long index);
private:
    IDispatch *engine_app;
};


#endif //SMARTEAM_COM_ENGINE_PROVIDER_H
