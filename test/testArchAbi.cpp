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

#include "./testArchAbi.h"
#include <pxr/arch/error.h>
#include <pxr/arch/library.h>
#include <pxr/arch/systemInfo.h>
#include <pxr/arch/vsnprintf.h>

#include <iostream>
#include <typeinfo>

using namespace pxr;

typedef arch::AbiBase2* (*NewDerived)();

int
main(int /*argc*/, char** /*argv*/)
{
    // Compute the plugin directory.
    std::string path = arch::GetExecutablePath();
    // Get directories.
    path = path.substr(0, path.find_last_of("/\\"));

    // Load the plugin and get the factory function.
#if defined(ARCH_OS_WINDOWS)
    path += "\\testArchAbiPlugin.dll";
#elif defined(ARCH_OS_DARWIN)
    path += "/libtestArchAbiPlugin.dylib";
#else
    path += "/libtestArchAbiPlugin.so";
#endif
    auto plugin = arch::LibraryOpen(path, ARCH_LIBRARY_LAZY);
    if (!plugin) {
        std::string error = arch::LibraryError();
        std::cerr << "Failed to load plugin: " << error << std::endl;
        ARCH_AXIOM(plugin);
    }

    NewDerived newPluginDerived = (NewDerived)arch::LibraryGetSymbolAddress(
        plugin, "newDerived");
    if (!newPluginDerived) {
        std::cerr << "Failed to find factory symbol" << std::endl;
        ARCH_AXIOM(newPluginDerived);
    }

    // Create a derived object in this executable and in the plugin.
    arch::AbiBase2* mainDerived = new arch::AbiDerived<int>;
    arch::AbiBase2* pluginDerived = newPluginDerived();

    // Compare.  The types should be equal and the dynamic cast should not
    // change the pointer.
    std::cout
        << "Derived types are equal: "
        << ((typeid(*mainDerived) == typeid(*pluginDerived)) ? "yes" : "no")
        << ", cast: " << pluginDerived
        << "->" << dynamic_cast<arch::AbiDerived<int>*>(pluginDerived)
        << std::endl;
    ARCH_AXIOM(typeid(*mainDerived) == typeid(*pluginDerived));
    ARCH_AXIOM(pluginDerived == dynamic_cast<arch::AbiDerived<int>*>(pluginDerived));

    return 0;
}
