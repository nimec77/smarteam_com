//
// Created by nim on 30.06.2021.
//

#include "engine_provider.h"

EngineProvider::~EngineProvider() {
    std::cout << "~EngineProvider start" << std::endl;
    engine_app->Release();
}

EngineProvider::EngineProvider(IDispatch *engine_App) : engine_app(engine_App) {}

IDispatch *EngineProvider::create_session(const wchar_t *application_name, const wchar_t *configuration_name) {
    DISPID dispid;
    const wchar_t *name = L"CreateSession";
    auto hr = engine_app->GetIDsOfNames(IID_NULL, const_cast<LPOLESTR *>(&name), 1, LOCALE_USER_DEFAULT,
                                        &dispid);
    if (FAILED(hr)) {
        std::string error = "EngineProvider create_session error:" + std::to_string(hr);
        std::cerr << error << std::endl;
        throw std::exception(error.c_str());
    }

    return nullptr;
}
