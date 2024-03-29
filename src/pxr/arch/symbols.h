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

#ifndef PXR_ARCH_SYMBOLS_H
#define PXR_ARCH_SYMBOLS_H

/// \file arch/symbols.h
/// Architecture-specific symbol lookup routines.

#include "./api.h"
#include <string>

namespace pxr {

namespace arch {

/// Returns information about the address \p address in the running program.
///
/// Returns \c false if no information can be found, otherwise returns \c true
/// and modifies the other arguments: \p objectPath is set to the absolute path 
/// to the executable or library the address is found in, \p baseAddress is the
/// address where that object is loaded, \p symbolName is the symbolic name of
/// the thing containing the address, and \p symbolAddress is the starting
/// address of that thing.  If no thing is found to contain the address then
/// \p symbolName is cleared and \p symbolAddress is set to \c NULL. Any of
/// the arguments except \p address can be \c NULL if the result isn't needed.
/// This will return \c false if \c NULL is passed to \p address.
///
ARCH_API
bool GetAddressInfo(void* address,
                    std::string* objectPath, void** baseAddress,
                    std::string* symbolName, void** symbolAddress);

}  // namespace arch

}  // namespace pxr

#endif // PXR_ARCH_SYMBOLS_H
