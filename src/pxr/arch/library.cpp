// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#include "./library.h"
#include "./errno.h"

#if defined(ARCH_OS_WINDOWS)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace pxr {

#if defined(ARCH_OS_WINDOWS)
namespace {
DWORD arch_lastLibraryError = 0;
}
#endif

void* ArchLibraryOpen(const std::string &filename, int flag)
{
#if defined(ARCH_OS_WINDOWS)
    arch_lastLibraryError = 0;
    if (void* result = LoadLibrary(filename.c_str())) {
        return result;
    }
    else {
        arch_lastLibraryError = GetLastError();
        return nullptr;
    }
#else
    // Clear any unchecked error first.
    (void)dlerror();
    return dlopen(filename.c_str(), flag);
#endif
}

std::string ArchLibraryError()
{
#if defined(ARCH_OS_WINDOWS)
    const DWORD error = arch_lastLibraryError;
    return error ? ArchStrSysError(error) : std::string();
#else
    const char* const error = dlerror();
    return error ? std::string(error) : std::string();
#endif
}

int ArchLibraryClose(void* handle)
{
#if defined(ARCH_OS_WINDOWS)
    arch_lastLibraryError = 0;
    // dlclose() returns 0 on success and non-zero on error, the opposite of
    // FreeLibrary().
    int status = ::FreeLibrary(reinterpret_cast<HMODULE>(handle)) ? 0 : -1;
    if (status) {
        arch_lastLibraryError = GetLastError();
    }
#else
    int status = dlclose(handle);
#endif
    return status;
}

void* ArchLibraryGetSymbolAddress(void* handle, const char* name)
{
#if defined(ARCH_OS_WINDOWS)
    return GetProcAddress(reinterpret_cast<HMODULE>(handle), name);
#else
    return dlsym(handle, name);
#endif
}

}  // namespace pxr
