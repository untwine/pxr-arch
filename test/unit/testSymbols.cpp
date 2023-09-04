// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
// Modified by Jeremy Retailleau.

#include <pxr/arch/symbols.h>
#include <gtest/gtest.h>

#include <cstdlib>

using namespace pxr;

static void Code() { }
static int data = 1;
static int bss;

static bool _GetLibraryPath(void* address, std::string* result)
{
    return arch::GetAddressInfo(address, result, NULL, NULL, NULL);
}

static std::string GetBasename(const std::string& path)
{
#if defined(ARCH_OS_WINDOWS)
    std::string::size_type i = path.find_last_of("/\\");
    if (i != std::string::npos) {
        std::string::size_type j = path.find(".exe");
        if (j != std::string::npos) {
            return path.substr(i + 1, j - i - 1);
        }
        return path.substr(i + 1);
    }
#else
    std::string::size_type i = path.rfind('/');
    if (i != std::string::npos) {
        return path.substr(i + 1);
    }
#endif
    return path;
}

TEST(SymbolsTest, GetAddressInfo)
{
    std::string path;

    // Invalid pointer.
    ASSERT_FALSE(_GetLibraryPath(0, &path));

    // Pointer to a local non-function.
    ASSERT_FALSE(_GetLibraryPath(&path, &path));

    // Pointer into the DATA section.
    ASSERT_TRUE(_GetLibraryPath(&data, &path));
    ASSERT_EQ(GetBasename(path), "testArchSymbols");

    // Pointer into the BSS section.
    ASSERT_TRUE(_GetLibraryPath(&bss, &path));
    ASSERT_EQ(GetBasename(path), "testArchSymbols");

    // Find this library.
    ASSERT_TRUE(_GetLibraryPath((void*)&Code, &path));
    ASSERT_EQ(GetBasename(path), "testArchSymbols");

    // Find another library.
    ASSERT_TRUE(_GetLibraryPath((void*)&exit, &path));
    ASSERT_NE(GetBasename(path), "testArchSymbols");
}
