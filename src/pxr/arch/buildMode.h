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

#ifndef PXR_ARCH_BUILD_MODE_H
#define PXR_ARCH_BUILD_MODE_H

#include "./defines.h"

namespace pxr {

namespace arch {

struct BuildMode {
// Check if the build system has specified a build mode, falling
// back to commonly-used macros if it has not. (Typically, _DEBUG
// is defined by Visual Studio and DEBUG by Xcode for debug-mode builds)
#if defined(BUILD_OPTLEVEL_DEV) || defined(_DEBUG) || defined(DEBUG)
    enum { DEV_BUILD = 1 };
#else
    enum { DEV_BUILD = 0 };
#endif
};

#define ARCH_DEV_BUILD pxr::arch::BuildMode::DEV_BUILD

}  // namespace arch

}  // namespace pxr

#endif // PXR_ARCH_BUILD_MODE_H
