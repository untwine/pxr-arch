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

#include "arch/defines.h"
#if defined(ARCH_OS_DARWIN)
#include <crt_externs.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <glob.h>
#include <limits.h>
#include <mach-o/dyld.h>
#include <mach-o/loader.h>
#include <mach-o/swap.h>
#include <mach/mach_time.h>
#include <sys/malloc.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <unistd.h>
#endif
#if defined(ARCH_OS_LINUX)
#include <dlfcn.h>
#include <glob.h>
#include <limits.h>
#include <sys/param.h>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <sys/statfs.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <ucontext.h>
#include <unistd.h>
#include <unwind.h>
#include <x86intrin.h>

#include <csignal>
#endif
#if defined(ARCH_OS_WINDOWS)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Memoryapi.h>
#include <Psapi.h>
#include <WinIoCtl.h>
#include <Windows.h>
#include <Winsock2.h>
#include <DbgHelp.h>
#include <direct.h>
#include <intrin.h>
#include <io.h>
#include <process.h>

#include <chrono>
#endif
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include <algorithm>
#include <atomic>
#include <cctype>
#include <cerrno>
#include <cinttypes>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <vector>
