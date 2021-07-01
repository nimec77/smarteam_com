//
// Created by nim on 30.06.2021.
//
#include "smarteam_provider.h"

SmarteamProvider::SmarteamProvider()  {
    std::cout << "SmarteamProvider start" << std::endl;

    CoInitialize(nullptr);

    CLSID clsid;

    auto hr = CLSIDFromProgID(kProgId, &clsid);

    if (FAILED(hr)) {
        std::string error = "SmarteamProvider CLSIDFromProgID error:" + std::to_string(hr);
        std::cerr << error << std::endl;
        throw std::exception(error.c_str());
    }

    hr = CoCreateInstance(clsid, nullptr, CLSCTX_LOCAL_SERVER, IID_IDispatch,
                          (void **) &smarteam_app);
    if (FAILED(hr)) {
        std::string error = "SmarteamProvider CoCreateInstance error:" + std::to_string(hr);
        std::cerr << error << std::endl;
        throw std::exception(error.c_str());
    }
}

SmarteamProvider::~SmarteamProvider() {
    std::cout << "~SmarteamProvider start" << std::endl;
    if (smarteam_app != nullptr) {
        smarteam_app->Release();
    }
}

IDispatch* SmarteamProvider::get_engine() {
    DISPID dispid;
    const wchar_t *name = L"Engine";
    auto hr = smarteam_app->GetIDsOfNames(IID_NULL, const_cast<LPOLESTR *>(&name), 1, LOCALE_USER_DEFAULT,
                                          &dispid);
    if (FAILED(hr)) {
        std::string error = "SmarteamProvider get_engine error:" + std::to_string(hr);
        std::cerr << error << std::endl;
        throw std::exception(error.c_str());
    }
    DISPPARAMS dp = {nullptr, nullptr, 0, 0 };
    VARIANT result;
    hr = smarteam_app->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                              nullptr,nullptr);
    if (FAILED(hr)) {
        std::string error = "SmarteamProvider get_engine error:" + std::to_string(hr);
        std::cerr << error << std::endl;
        throw std::exception(error.c_str());
    }

    return result.pdispVal;
}
