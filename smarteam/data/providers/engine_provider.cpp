//
// Created by nim on 30.06.2021.
//

#include "engine_provider.h"

EngineProvider::EngineProvider(IDispatch *engine_app) : engine_app(engine_app) {}

EngineProvider::~EngineProvider() {
  std::cout << "~EngineProvider start" << std::endl;
  data_helper::safe_release(engine_app);
}

IDispatch *EngineProvider::create_session(const wchar_t *application_name, const wchar_t *configuration_name) {

  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*engine_app), L"CreateSession");

  DISPPARAMS dp = {nullptr, nullptr, 0, 0};

  VARIANT args[2];
  args[0].vt = VT_BSTR;
  args[0].bstrVal = SysAllocString(application_name);
  args[1].vt = VT_BSTR;
  args[1].bstrVal = SysAllocString(configuration_name);
  dp.rgvarg = args;
  dp.cArgs = 2;
  dp.cNamedArgs = 0;

  VARIANT result;
  VariantInit(&result);
  auto hr = engine_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &result,
                               nullptr, nullptr);
  VariantClear(args);
  if (FAILED(hr)) {
    std::string error = "EngineProvider::create_session error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  return result.pdispVal;
}

IDispatch *EngineProvider::get_database(long index) {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*engine_app), L"Databases");

  DISPPARAMS dp = {nullptr, nullptr, 0, 0};

  VARIANT base_index;
  base_index.vt = VT_INT;
  base_index.intVal = index;
  dp.rgvarg = &base_index;
  dp.cArgs = 1;
  dp.cNamedArgs = 0;

  VARIANT result;
  VariantInit(&result);
  auto hr = engine_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                               nullptr, nullptr);
  VariantClear(&base_index);
  if (FAILED(hr)) {
    std::string error = "EngineProvider::get_database error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  return result.pdispVal;
}
