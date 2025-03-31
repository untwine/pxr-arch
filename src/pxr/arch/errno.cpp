// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#include "pxr/arch/pxr.h"
#include "pxr/arch/errno.h"
#include <cerrno>
#include <cstring>
#if defined(ARCH_OS_WINDOWS)
#include <Windows.h>
#endif
#if defined(ARCH_OS_WASM_VM)
#include <locale.h>
#endif

ARCH_NAMESPACE_OPEN_SCOPE

// POSIX strerror_r: returns int, writes to buffer
inline char* check_error(int result, char* msg_buf, int errorCode) {
    if (result != 0) {
        snprintf(msg_buf, 256, "unknown error: %d", errorCode);
    }
    return msg_buf;
}

// GNU strerror_r: returns char*
inline char* check_error(char* result, char*, int) {
    return result;
}

std::string
ArchStrerror()
{
    return ArchStrerror(errno);
}

std::string
ArchStrerror(int errorCode)
{
    char msg_buf[256];

#if defined(ARCH_OS_WASM_VM)
    locale_t locale = newlocale(LC_ALL_MASK, "C", NULL);
    if (locale == (locale_t)0) {
        return "Failed to create locale";
    }
    const char* msg = strerror_l(errorCode, locale);
    freelocale(locale);
    if (msg == nullptr) {
        return "Unknown error code";
    }
    return std::string(msg);
#elif defined(_GNU_SOURCE)
    return check_error(
        strerror_r(errorCode, msg_buf, 256), msg_buf, errorCode);
#elif !defined(ARCH_COMPILER_MSVC)
    strerror_r(errorCode, msg_buf, 256);
#else
    strerror_s(msg_buf, 256, errorCode);
#endif // _GNU_SOURCE
    return msg_buf;
}

#if defined(ARCH_OS_WINDOWS)
std::string ArchStrSysError(unsigned long errorCode)
{
    if(errorCode == 0)
        return std::string();

    LPSTR buffer = nullptr;
    size_t len = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                               FORMAT_MESSAGE_FROM_SYSTEM |
                               FORMAT_MESSAGE_IGNORE_INSERTS,
                               nullptr,
                               errorCode,
                               MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                               (LPSTR)&buffer,
                               0,
                               nullptr);
    std::string message(buffer, len);
    LocalFree(buffer);

    return message;
}
#endif

ARCH_NAMESPACE_CLOSE_SCOPE
