//
// Created by nim on 01.07.2021.
//

#include "helper.h"

namespace helper {

const char *utf16_to_utf8(const wchar_t *utf16_str) {
  auto size = WideCharToMultiByte(
      65001,
      0,
      utf16_str,
      -1,
      nullptr,
      0,
      nullptr,
      nullptr
  );

  if (size == 0) {
    std::string error = "utf16_to_utf8: error get string length!";
    std::cerr << error << std::endl;
    throw std::length_error(error);
  }

//  std::cout << "String length: " << size << std::endl;

  const auto result = new char[size];

  size = WideCharToMultiByte(
      65001,
      0,
      utf16_str,
      -1,
      result,
      size,
      nullptr,
      nullptr
  );
  if (size == 0) {
    std::string error = "utf16_to_utf8: error translate string to utf8";
    std::cerr << error << std::endl;
    throw std::exception(error.c_str());
  }

//  std::cout << "Translate string: " << result << std::endl;

  return result;
}

const wchar_t *bstr_to_wchar(BSTR bstr) {
  auto bs = _bstr_t(bstr, true);

//  auto wide_size = bs.length();
//  auto *ws = new wchar_t [wide_size];
//  wcscpy_s(ws, wide_size, bs);
//
//  std::wcout << L"Password:" << ws << std::endl;

  return bs;
}

}
