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

#include "arch/attributes.h"
#include "arch/stackTrace.h"
#include "arch/systemInfo.h"

namespace arch {

void _InitDebuggerAttach();
void _InitTmpDir();
void _SetAppLaunchTime();
void _ValidateAssumptions();
void _InitTickTimer();

namespace {

ARCH_CONSTRUCTOR(_InitConfig, 2, void)
{
    // Initialize the application start time.  First so it's a close as
    // possible to the real start time.
    _SetAppLaunchTime();

    // Initialize the temp directory.  Early so other initialization
    // functions can use it.
    _InitTmpDir();

    // Initialize program name for errors.  Early for initialization
    // error reporting.
    SetProgramNameForErrors(GetExecutablePath().c_str());

    // Perform platform validations: these are very quick, lightweight
    // checks.  The reason that we call this function here is that pretty
    // much any program that uses anything from lib/tf will end up here
    // at some point.  It is not so important that *every* program
    // perform this check; what is important is that when we bring up a new
    // architecture/compiler/build, the validation gets performed at some
    // point, to alert us to any problems.
    _ValidateAssumptions();

    // Initialize the tick timer.
    _InitTickTimer();

    // Initialize the debugger interface.
    _InitDebuggerAttach();
}

}  // namespace

}  // namespace arch
