//
// Created by nim on 01.07.2021.
//

#ifndef SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_
#define SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_

#include <iostream>
#include <sstream>
#include <windows.h>

#include <data/data_helper.h>
#include <constants.h>


class DatabaseProvider {
 public:
  explicit DatabaseProvider(IDispatch *database_app);

  virtual ~DatabaseProvider();

  virtual _bstr_t get_alias();

  virtual _bstr_t get_password();

 private:
  IDispatch *database_app;
};

#endif //SMARTEAM_COM_SMARTEAM_DATA_PROVIDERS_DATABASE_PROVIDER_H_
