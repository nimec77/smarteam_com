//
// Created by nim on 01.07.2021.
//

#include "session_provider.h"

SessionProvider::SessionProvider(IDispatch *session_app) : session_app(session_app) {}

SessionProvider::~SessionProvider() {
  std::cout << "~EngineProvider start" << std::endl;
  data_helper::safe_release(session_app);
}
IDispatch *SessionProvider::open_database_connection(_bstr_t& connection_string,
                                                     _bstr_t& database_password,
                                                     bool password_is_encoded) {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*session_app),
                                            kOpenDatabaseConnection);

  DISPPARAMS dp = {nullptr, nullptr, 0, 0};

  VARIANT args[3];
  args[0].vt = VT_BOOL;
  args[0].boolVal = password_is_encoded ? VARIANT_TRUE : VARIANT_FALSE;
  args[1].vt = VT_BSTR;
  args[1].bstrVal = database_password;
  args[2].vt = VT_BSTR;
  args[2].bstrVal = connection_string;
  dp.rgvarg = args;
  dp.cArgs = 3;
  dp.cNamedArgs = 0;

  VARIANT result;
  VariantInit(&result);
  auto hr = session_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &result,
                                nullptr, nullptr);
  for (auto & arg : args) {
    VariantClear(&arg);
  }
  if (FAILED(hr)) {
    std::string error = "SessionProvider::open_database_connection error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  return result.pdispVal;
}
bool SessionProvider::user_logged_on() {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*session_app), kUserLoggedOn);
  DISPPARAMS dp = {nullptr, nullptr, 0, 0 };
  VARIANT result;
  VariantInit(&result);
  auto hr = session_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dp, &result,
                                 nullptr, nullptr);
  if (FAILED(hr)) {
    std::string error = "SessionProvider::user_logged_on error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  return result.boolVal == VARIANT_TRUE;
}
bool SessionProvider::user_login(_bstr_t& user_name, _bstr_t& password) {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*session_app),
                                            kUserLogin);

  DISPPARAMS dp = {nullptr, nullptr, 0, 0};

  VARIANT args[2];
  args[0].vt = VT_BSTR;
  args[0].bstrVal = password;
  args[1].vt = VT_BSTR;
  args[1].bstrVal = user_name;
  dp.rgvarg = args;
  dp.cArgs = 2;
  dp.cNamedArgs = 0;

  VARIANT result;
  VariantInit(&result);
  auto hr = session_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &result,
                                nullptr, nullptr);
  if (FAILED(hr)) {
    std::string error = "SessionProvider::user_login error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  return result.boolVal == VARIANT_TRUE;

  return false;
}
