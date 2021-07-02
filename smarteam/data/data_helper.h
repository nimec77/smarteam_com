//
// Created by nim on 01.07.2021.
//

#ifndef SMARTEAM_COM_DATA_HELPER_H
#define SMARTEAM_COM_DATA_HELPER_H

#include <iostream>
#include <sstream>
#include <windows.h>
#include <map>

#include "../helper.h"

namespace data_helper {
DISPID get_names(IDispatch &dispatch, const wchar_t *name);

void safe_release(IDispatch *dispatch);

void get_dispatch_methods(IDispatch *dispatch);
}

#endif //SMARTEAM_COM_DATA_HELPER_H
