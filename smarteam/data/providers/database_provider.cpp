//
// Created by nim on 01.07.2021.
//

#include "database_provider.h"
DatabaseProvider::DatabaseProvider(IDispatch *database_app) : database_app(database_app) {}

DatabaseProvider::~DatabaseProvider() {
  std::cout << "~DatabaseProvider start" << std::endl;
  data_helper::safe_release(database_app);
}
_bstr_t DatabaseProvider::get_alias() {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*database_app), kAlias);

  DISPPARAMS dp = {nullptr, nullptr, 0, 0};

  VARIANT result;
  VariantInit(&result);
  auto hr = database_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                 nullptr, nullptr);
  if (FAILED(hr)) {
    std::string error = "DatabaseProvider::get_alias error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  return _bstr_t(result.bstrVal);
}
_bstr_t DatabaseProvider::get_password() {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*database_app), kPassword);

  DISPPARAMS dp = {nullptr, nullptr, 0, 0};

  VARIANT result;
  VariantInit(&result);
  auto hr = database_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                 nullptr, nullptr);

  if (FAILED(hr)) {
    std::string error = "DatabaseProvider::get_password error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  return  _bstr_t(result.bstrVal);
}
