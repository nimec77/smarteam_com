//
// Created by nim on 01.07.2021.
//

#ifndef SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_
#define SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_

#include <iostream>
#include <sstream>
#include <windows.h>
#include <data/data_helper.h>

class SessionProvider {
 public:
  explicit SessionProvider(IDispatch *session_app);

  virtual ~SessionProvider();

  virtual IDispatch *open_database_connection(const wchar_t *connection_string,
                                              const wchar_t *database_password,
                                              bool password_is_encoded);
 private:
  IDispatch *session_app;
};

#endif //SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_SESSION_PROVIDER_H_
