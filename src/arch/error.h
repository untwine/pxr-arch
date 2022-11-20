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

#ifndef ARCH_ERROR_H
#define ARCH_ERROR_H

/// \file arch/error.h
/// \ingroup group_Diagnostics
/// Low-level fatal error reporting.

#include <cstddef>

#include "arch/api.h"
#include "arch/defines.h"
#include "arch/functionLite.h"

namespace arch {

/// Print message to standard error and abort program.
///
/// \param msg The reason for the failure.
/// \param funcName The name of the function that \c _Error was called from.
/// \param lineNo The line number of the file that \c _Error was called from.
/// \param fileName The name of the file that \c _Error was called from.
///
/// \private
[[noreturn]] ARCH_API void _Error(
    const char* msg, const char* funcName, size_t lineNo, const char* fileName);

/// Print warning message to standard error, but continue execution.
///
/// \param msg The reason for the warning.
/// \param funcName The name of the function that \c _Warning was called from.
/// \param lineNo The line number of the file that \c _Warning was called from.
/// \param fileName The name of the file that \c _Warning was called from.
///
/// \private
ARCH_API
void _Warning(
    const char* msg, const char* funcName, size_t lineNo, const char* fileName);

/// \addtogroup group_Diagnostics
///@{

/// Unconditionally aborts the program.
///
/// \param msg is a literal string, a \c const \c char* (but not
///        an \c std::string) that describes why the program is aborting.
/// \hideinitializer
#define ARCH_ERROR(msg) _Error(msg, __ARCH_FUNCTION__, __LINE__, __ARCH_FILE__)

/// Prints a warning message to stderr.
///
/// \param msg is a literal string, a \c const \c char* (but not
///        an \c std::string).
/// \hideinitializer
#define ARCH_WARNING(msg) \
    _Warning(msg, __ARCH_FUNCTION__, __LINE__, __ARCH_FILE__)

/// Aborts the program if \p cond evaluates to false.
/// \hideinitializer
#define ARCH_AXIOM(cond) \
    if (!(cond)) ARCH_ERROR("[" #cond "] axiom failed")

///@}

}  // namespace arch

#endif  // ARCH_ERROR_H
