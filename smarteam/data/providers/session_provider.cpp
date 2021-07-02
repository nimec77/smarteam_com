//
// Created by nim on 01.07.2021.
//

#include "session_provider.h"
//#include <propvarutil.h>

SessionProvider::SessionProvider(IDispatch *session_app) : session_app(session_app) {}

SessionProvider::~SessionProvider() {
  data_helper::safe_release(session_app);
}
IDispatch *SessionProvider::open_database_connection(const wchar_t *connection_string,
                                                     const wchar_t *database_password,
                                                     bool password_is_encoded) {
  auto dispatch_id = data_helper::get_names(reinterpret_cast<IDispatch &>(*session_app),
                                            L"OpenDatabaseConnection");

  DISPPARAMS dp = {nullptr, nullptr, 0, 0};

  VARIANT args[3];
  args[0].vt = VT_BSTR;
  args[0].bstrVal = SysAllocString(connection_string);
  args[1].vt = VT_BSTR;
  args[1].bstrVal = SysAllocString(database_password);
  args[2].vt = VT_BOOL;
  args[2].boolVal = password_is_encoded ? VARIANT_TRUE : VARIANT_FALSE;
  dp.rgvarg = args;
  dp.cArgs = 3;
  dp.cNamedArgs = 0;

  VARIANT result;
  VariantInit(&result);
  auto hr = session_app->Invoke(dispatch_id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dp, &result,
                                nullptr, nullptr);
//  auto hr = _com_dispatch_method(session_app,
//                                 dispatch_id,
//                                 DISPATCH_METHOD,
//                                 VT_DISPATCH,
//                                 &result,
//                                 L"\0x0008\0x0008\0x0011",
//                                 connection_string,
//                                 database_password,
//                                 password_is_encoded);
  VariantClear(args);
  if (FAILED(hr)) {
    std::string error = "SessionProvider::open_database_connection error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  return result.pdispVal;
}
