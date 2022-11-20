// Copyright 2022 Pixar
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
// Modified by Jeremy Retailleau

#ifndef ARCH_ENV_H
#define ARCH_ENV_H

#include <string>

#include "arch/api.h"

namespace arch {

///
/// Architecture dependent access to environment variables.
/// \ingroup group_SystemFunctions
///

///
/// Returns \c true if and only if the current environment contains \c name.
/// \ingroup group_SystemFunctions
///
ARCH_API
bool HasEnv(const std::string &name);

///
/// Gets a value from the current environment identified by \c name.
/// \ingroup group_SystemFunctions
///
ARCH_API
std::string GetEnv(const std::string &name);

///
/// Creates or modifies an environment variable.
/// \ingroup group_SystemFunctions
///
ARCH_API
bool SetEnv(const std::string &name, const std::string &value, bool overwrite);

///
/// Removes an environment variable.
/// \ingroup group_SystemFunctions
///
ARCH_API
bool RemoveEnv(const std::string &name);

///
/// Expands environment variables in \c str.
/// \ingroup group_SystemFunctions
///
ARCH_API
std::string ExpandEnvironmentVariables(const std::string &str);

///
/// Return an array of the environment variables.
/// \ingroup group_SystemFunctions
///
ARCH_API
char **Environ();

}  // namespace arch

#endif  // ARCH_ENV_H
