//
// Created by nim on 01.07.2021.
//

#ifndef SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_
#define SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_

#include <iostream>
#include <sstream>
#include <windows.h>
#include <data/data_helper.h>
#include <constants.h>

class SessionProvider {
 public:
  explicit SessionProvider(IDispatch *session_app);

  virtual ~SessionProvider();

  virtual IDispatch *open_database_connection(_bstr_t& connection_string,
                                              _bstr_t& database_password,
                                              bool password_is_encoded);

  virtual bool user_logged_on();

  virtual bool user_login(_bstr_t& user_name, _bstr_t& password);

 private:
  IDispatch *session_app;
};

#endif //SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_
