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

#ifndef PXR_ARCH_TEST_ABI_H
#define PXR_ARCH_TEST_ABI_H

#include <pxr/arch/api.h>

namespace pxr {

namespace archTest {

struct AbiBase1 {
    void* dummy;
};

struct AbiBase2 {
    virtual ~AbiBase2() = default;
    virtual const char* name() const = 0;
};

template <class T>
struct AbiDerived : public AbiBase1, public AbiBase2 {
    AbiDerived() : AbiBase1(), AbiBase2() {}
    ~AbiDerived() override = default;
    const char* name() const override { return "AbiDerived"; }
};

}  // namespace archTest

}  // namespace pxr

#endif  // PXR_ARCH_TEST_ABI_H
