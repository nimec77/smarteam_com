//
// Created by nim on 30.06.2021.
//
#include "smarteam_provider.h"
#include "../data_helper.h"


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
    data_helper::safe_release(smarteam_app);
}

IDispatch* SmarteamProvider::get_engine() {
    auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*smarteam_app), L"Engine");
    DISPPARAMS dp = {nullptr, nullptr, 0, 0 };
    VARIANT result;
    VariantInit(&result);
    auto hr = smarteam_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                   nullptr, nullptr);
    if (FAILED(hr)) {
        std::string error = "SmarteamProvider::get_engine error:" + std::to_string(hr);
        std::cerr << error << std::endl;
        throw std::exception(error.c_str());
    }

    return result.pdispVal;
}
