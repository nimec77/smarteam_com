//
// Created by nim on 01.07.2021.
//

#include "data_helper.h"

byte buffer[4 * 1024];

namespace data_helper {
DISPID get_names(IDispatch &dispatch, const wchar_t *name) {
  DISPID dispid;

  auto hr = dispatch.GetIDsOfNames(IID_NULL, const_cast<LPOLESTR *>(&name), 1, LOCALE_USER_DEFAULT,
                                   &dispid);
  if (FAILED(hr)) {
    auto str = std::string(helper::utf16_to_utf8(name));
    std::string error = "data_helper::get_name '" + str + "' error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());

  }
  return dispid;
}

void safe_release(IDispatch *dispatch) {
  if (dispatch != nullptr) {
    dispatch->Release();
    dispatch = nullptr;
  }
}
void get_dispatch_methods(IDispatch *dispatch) {

  auto hr = dispatch->GetTypeInfo(0, 0, reinterpret_cast<ITypeInfo **>(&buffer));

  if (FAILED(hr)) {
    std::string error = "data_helper::get_dispatch_methods error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

  auto *info = reinterpret_cast<ITypeInfo *>(&buffer);

  TYPEATTR *attr = nullptr;

  hr = info->GetTypeAttr(&attr);
  if (FAILED(hr)) {
    std::string error = "data_helper::get_dispatch_methods error:" + std::to_string(hr);
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }
  FUNCDESC *fd = nullptr;
  for (auto i = 0; i < attr->cFuncs; ++i) {
    hr = info->GetFuncDesc(i, &fd);
    if (FAILED(hr)) {
      std::string error = "data_helper::get_dispatch_methods error:" + std::to_string(hr);
      std::cerr << error << std::endl;
      throw std::exception(error.c_str());
    }
    _bstr_t func_name;
    info->GetDocumentation(fd->memid, func_name.GetAddress(), nullptr, nullptr, nullptr);
    if (func_name.length() > 0) {
      auto wide_size = func_name.length();
      auto *ws = new wchar_t[wide_size];
      wcscpy_s(ws, wide_size, func_name);

      std::wcout << ws << std::endl;
    }
    info->ReleaseFuncDesc(fd);
  }
  info->ReleaseTypeAttr(attr);
}

}
