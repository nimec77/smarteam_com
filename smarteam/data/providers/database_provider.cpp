//
// Created by nim on 01.07.2021.
//

#include "database_provider.h"
DatabaseProvider::DatabaseProvider(IDispatch *database_app) : database_app(database_app) {}

DatabaseProvider::~DatabaseProvider() {
  std::cout << "~DatabaseProvider start" << std::endl;
  data_helper::safe_release(database_app);
}
const wchar_t *DatabaseProvider::get_alias() {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*database_app), L"Alias");

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

  return reinterpret_cast<const wchar_t *>(result.pbstrVal);
}
const wchar_t *DatabaseProvider::get_password() {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*database_app), L"Password");

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

  return  helper::bstr_to_wchar(result.bstrVal);
}
