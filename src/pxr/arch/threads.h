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

#ifndef PXR_ARCH_THREADS_H
#define PXR_ARCH_THREADS_H

/// \file arch/threads.h
/// Architecture-specific thread function calls.

#include "./api.h"
#include "./defines.h"

// Needed for ARCH_SPIN_PAUSE on Windows in builds with precompiled
// headers disabled.
#ifdef ARCH_COMPILER_MSVC
#include <intrin.h>
#endif

#include <thread>

namespace pxr {

namespace arch {

/// Return true if the calling thread is the main thread, false otherwise.
ARCH_API bool IsMainThread();

/// Return the std::thread_id for the thread arch considers to be the "main"
/// thread.
ARCH_API std::thread::id GetMainThreadId();

/// ARCH_SPIN_PAUSE -- 'pause' on x86, 'yield' on arm.
#if defined(ARCH_CPU_INTEL)
#if defined(ARCH_COMPILER_GCC) || defined(ARCH_COMPILER_CLANG)
#define ARCH_SPIN_PAUSE() __builtin_ia32_pause()
#elif defined(ARCH_COMPILER_MSVC)
#define ARCH_SPIN_PAUSE() _mm_pause()
#endif
#elif defined(ARCH_CPU_ARM)
#if defined(ARCH_COMPILER_GCC) || defined(ARCH_COMPILER_CLANG)
#define ARCH_SPIN_PAUSE() asm volatile ("yield" ::: "memory")
#elif defined(ARCH_COMPILER_MSVC)
#define ARCH_SPIN_PAUSE() __yield();
#endif
#else
#define ARCH_SPIN_PAUSE()
#endif

}  // namespace arch

}  // namespace pxr

#endif // PXR_ARCH_THREADS_H
