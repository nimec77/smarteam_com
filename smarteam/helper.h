//
// Created by nim on 01.07.2021.
//

#ifndef SMARTEAM_COM_HELPER_H
#define SMARTEAM_COM_HELPER_H

#include <iostream>
#include <sstream>
#include <windows.h>
#include <comdef.h>

namespace helper {
const char *utf16_to_utf8(const wchar_t *utf16_str);

const wchar_t *bstr_to_wchar(BSTR bstr);

}
#endif //SMARTEAM_COM_HELPER_H
