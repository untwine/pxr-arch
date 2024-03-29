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

#ifndef PXR_ARCH_DEMANGLE_H
#define PXR_ARCH_DEMANGLE_H

#if !defined(__cplusplus)
#error This include file can only be included in C++ programs.
#endif

/// \file arch/demangle.h
/// Demangle C++ typenames generated by the \c typeid() facility.

#include "./api.h"
#include <string>
#include <typeinfo>
#include <typeindex>

namespace pxr {

namespace arch {

/// Demangle RTTI-generated type name.
///
/// Given a variable \c v, the construct \c typeid(v).name() returns
/// the type-name of \c v; unfortunately, the returned type-name is
/// sometimes extremely encoded (otherwise known as "mangled").
/// \c Demangle parses the passed in type-name \c typeName into a
/// readable form, and overwrites \c typeName.  If \c typeName
/// cannot be unmangled, the function returns \c false without altering
/// \c typeName. Otherwise \c true is returned.
ARCH_API bool Demangle(std::string* typeName);

/// Return demangled RTTI-generated type name.
///
/// If \c typeName can be demangled, the function returns the demangled
/// string; otherwise, the function returns the empty string.
///
/// \see Demangle()
ARCH_API std::string
GetDemangled(const std::string& typeName);

/// Return demangled RTTI-generated type name.
///
/// \see Demangle()
/// \overload
ARCH_API std::string
GetDemangled(const char *typeName);

/// Return demangled RTTI-generated type name.
///
/// Returns the demangled name associated with typeInfo (i.e. typeInfo.name()).
///
/// \see Demangle()
/// \overload
inline std::string
GetDemangled(const std::type_info& typeInfo) {
    return GetDemangled(typeInfo.name());
}

/// Return demangled RTTI-generated type name.
///
/// Returns the demangled name associated with typeIndex (i.e. typeIndex.name()).
///
/// \see Demangle()
/// \overload
inline std::string
GetDemangled(const std::type_index& typeIndex) {
    return GetDemangled(typeIndex.name());
}

/// Return demangled RTTI generated-type name.
///
/// Returns the demangled name of type T.
///
/// \see Demangle()
/// \overload
template <typename T>
inline std::string
GetDemangled() {
    return GetDemangled(typeid(T).name());
}

/// \private
ARCH_API
void _DemangleFunctionName(std::string* functionName);

}  // namespace arch

}  // namespace pxr

#endif	// PXR_ARCH_DEMANGLE_H
