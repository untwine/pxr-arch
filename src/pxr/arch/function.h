// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#ifndef PXR_ARCH_FUNCTION_H
#define PXR_ARCH_FUNCTION_H

/// \file arch/function.h
/// Define preprocessor function name macros.
///
/// This file extents the functionality of pxr/arch/functionLite.h.
/// This file needs to be public but shouldn't be included directly by
/// anything outside of \c lib/tf.

#include "pxr/arch/pxr.h"
#include "pxr/arch/api.h"
#include "pxr/arch/functionLite.h"
#include <string>

ARCH_NAMESPACE_OPEN_SCOPE

/// Return well formatted function name.
///
/// This function assumes \c function is __ARCH_FUNCTION__ and
/// \c prettyFunction is __ARCH_PRETTY_FUNCTION__, and attempts to
/// reconstruct a well formatted function name.
///
/// \ingroup group_arch_Diagnostic
ARCH_API
std::string ArchGetPrettierFunctionName(const std::string &function,
                                        const std::string &prettyFunction);

ARCH_NAMESPACE_CLOSE_SCOPE

#endif // PXR_ARCH_FUNCTION_H
