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

#include <pxr/arch/library.h>
#include <pxr/arch/systemInfo.h>
#include <archTest/abi.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <string>

using namespace pxr;

TEST(ArchABITest, GetExecutablePath)
{
    std::string path = arch::GetExecutablePath();
    std::string root = std::getenv("EXE_PATH");
#if defined(ARCH_OS_WINDOWS)
    std::string expected = root + "\\testArchAbi.exe";
#else
    std::string expected = root + "/testArchAbi";
#endif
    ASSERT_EQ(path, expected);
}

TEST(ArchABITest, Library)
{
    std::string path = std::getenv("PLUGIN_PATH");
#if defined(ARCH_OS_WINDOWS)
    path += "\\archTestPlugin.dll";
#elif defined(ARCH_OS_DARWIN)
    path += "/libarchTestPlugin.dylib";
#else
    path += "/libarchTestPlugin.so";
#endif
    auto plugin = arch::LibraryOpen(path, ARCH_LIBRARY_LAZY);
    ASSERT_NE(plugin, nullptr);
    ASSERT_EQ(arch::LibraryError(), "");

    // Get symbol from library.
    using NewDerived = archTest::AbiBase2* (*)();
    auto newPluginDerived =
        (NewDerived)arch::LibraryGetSymbolAddress(plugin, "newDerived");
    ASSERT_NE(newPluginDerived, nullptr);

    // Fail to get symbol from library.
    auto symbol =
        (NewDerived)arch::LibraryGetSymbolAddress(plugin, "incorrect");
    ASSERT_EQ(symbol, nullptr);

    // Create a derived object in this executable and in the plugin.
    archTest::AbiBase2* mainDerived = new archTest::AbiDerived<int>;
    archTest::AbiBase2* pluginDerived = newPluginDerived();

    // The types should be equal and the dynamic cast should not
    // change the pointer.
    ASSERT_EQ(typeid(*mainDerived), typeid(*pluginDerived));
    ASSERT_EQ(
        pluginDerived, dynamic_cast<archTest::AbiDerived<int>*>(pluginDerived));

    auto status = arch::LibraryClose(plugin);
    ASSERT_EQ(status, 0);
}

TEST(ArchABITest, LibraryOpenError)
{
    std::string path = "/incorrect";
    auto plugin = arch::LibraryOpen(path, ARCH_LIBRARY_LAZY);
    ASSERT_EQ(plugin, nullptr);
    ASSERT_NE(arch::LibraryError(), "");
}
