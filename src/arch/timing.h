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

#ifndef ARCH_TIMING_H
#define ARCH_TIMING_H

/// \file arch/timing.h
/// \ingroup group_SystemFunctions
/// High-resolution, low-cost timing routines.

#include "arch/api.h"
#include "arch/defines.h"
#include "arch/inttypes.h"

/// \addtogroup group_SystemFunctions
///@{

#if defined(ARCH_OS_LINUX) && defined(ARCH_CPU_INTEL)
#include <x86intrin.h>
#elif defined(ARCH_OS_DARWIN)
#include <mach/mach_time.h>
#elif defined(ARCH_OS_WINDOWS)
#include <intrin.h>
#endif

#include <algorithm>
#include <atomic>
#include <iterator>
#include <numeric>

namespace arch {

/// Return the current time in system-dependent units.
///
/// The current time is returned as a number of "ticks", where each tick
/// represents some system-dependent amount of time.  The resolution of the
/// timing routines varies, but on all systems, it is well under one
/// microsecond.  The cost of this routine is in the 10s-to-100s of nanoseconds
/// on GHz class machines.
inline uint64_t GetTickTime()
{
#if defined(ARCH_OS_DARWIN)
    // On Darwin we'll use mach_absolute_time().
    return mach_absolute_time();
#elif defined(ARCH_CPU_INTEL)
    // On Intel we'll use the rdtsc instruction.
    return __rdtsc();
#elif defined(ARCH_CPU_ARM)
    uint64_t result;
    __asm __volatile("mrs	%0, CNTVCT_EL0" : "=&r"(result));
    return result;
#else
#error Unknown architecture.
#endif
}


/// Get a "start" tick time for measuring an interval of time, followed by a
/// later call to GetStopTickTime().  Or see IntervalTimer.  This is
/// like GetTickTime but it includes compiler & CPU fencing & reordering
/// constraints in an attempt to get the best measurement possible.
inline uint64_t GetStartTickTime()
{
    uint64_t t;
#if defined(ARCH_OS_DARWIN)
    return GetTickTime();
#elif defined(ARCH_CPU_ARM)
    std::atomic_signal_fence(std::memory_order_seq_cst);
    asm volatile("mrs %0, cntvct_el0" : "=r"(t));
    std::atomic_signal_fence(std::memory_order_seq_cst);
#elif defined(ARCH_COMPILER_MSVC)
    _mm_lfence();
    std::atomic_signal_fence(std::memory_order_seq_cst);
    t = __rdtsc();
    _mm_lfence();
    std::atomic_signal_fence(std::memory_order_seq_cst);
#elif defined(ARCH_CPU_INTEL) \
    && (defined(ARCH_COMPILER_CLANG) || defined(ARCH_COMPILER_GCC))
    // Prevent reorders by the compiler.
    std::atomic_signal_fence(std::memory_order_seq_cst);
    asm volatile(
        "lfence\n\t"
        "rdtsc\n\t"
        "shl $32, %%rdx\n\t"
        "or %%rdx, %0\n\t"
        "lfence"
        : "=a"(t)
        :
        // rdtsc writes rdx
        // shl modifies cc flags
        : "rdx", "cc");
#else
#error "Unsupported architecture."
#endif
    return t;
}

/// Get a "stop" tick time for measuring an interval of time.  See
/// GetStartTickTime() or IntervalTimer.  This is like GetTickTime
/// but it includes compiler & CPU fencing & reordering constraints in an
/// attempt to get the best measurement possible.
inline uint64_t GetStopTickTime()
{
    uint64_t t;
#if defined(ARCH_OS_DARWIN)
    return GetTickTime();
#elif defined(ARCH_CPU_ARM)
    std::atomic_signal_fence(std::memory_order_seq_cst);
    asm volatile("mrs %0, cntvct_el0" : "=r"(t));
    std::atomic_signal_fence(std::memory_order_seq_cst);
#elif defined(ARCH_COMPILER_MSVC)
    std::atomic_signal_fence(std::memory_order_seq_cst);
    unsigned aux;
    t = __rdtscp(&aux);
    _mm_lfence();
    std::atomic_signal_fence(std::memory_order_seq_cst);
#elif defined(ARCH_CPU_INTEL) \
    && (defined(ARCH_COMPILER_CLANG) || defined(ARCH_COMPILER_GCC))
    std::atomic_signal_fence(std::memory_order_seq_cst);
    asm volatile(
        "rdtscp\n\t"
        "shl $32, %%rdx\n\t"
        "or %%rdx, %0\n\t"
        "lfence"
        : "=a"(t)
        :
        // rdtscp writes rcx & rdx
        // shl modifies cc flags
        : "rcx", "rdx", "cc");
#else
#error "Unsupported architecture."
#endif
    return t;
}

#if defined(doxygen)                                        \
    || (!defined(ARCH_OS_DARWIN) && defined(ARCH_CPU_INTEL) \
        && (defined(ARCH_COMPILER_CLANG) || defined(ARCH_COMPILER_GCC)))

/// A simple timer class for measuring an interval of time using the
/// TickTimer facilities.
struct IntervalTimer {
    /// Construct a timer and start timing if \p start is true.
    explicit IntervalTimer(bool start = true) : _started(start)
    {
        if (_started) {
            Start();
        }
    }

    /// Start the timer, or reset the start time if it has already been started.
    void Start()
    {
        _started = true;
        std::atomic_signal_fence(std::memory_order_seq_cst);
        asm volatile(
            "lfence\n\t"
            "rdtsc\n\t"
            "lfence"
            : "=a"(_startLow), "=d"(_startHigh)::);
    }

    /// Return true if this timer is started.
    bool IsStarted() const { return _started; }

    /// Return this timer's start time, or 0 if it hasn't been started.
    uint64_t GetStartTicks() const
    {
        return (uint64_t(_startHigh) << 32) + _startLow;
    }

    /// Read and return the current time.
    uint64_t GetCurrentTicks() { return GetStopTickTime(); }

    /// Read the current time and return the difference between it and the start
    /// time.  If the timer was not started, return 0.
    uint64_t GetElapsedTicks()
    {
        if (!_started) {
            return 0;
        }
        uint32_t stopLow, stopHigh;
        std::atomic_signal_fence(std::memory_order_seq_cst);
        asm volatile(
            "rdtscp\n\t"
            "lfence"
            : "=a"(stopLow), "=d"(stopHigh)
            :
            // rdtscp writes rcx
            : "rcx");
        return (uint64_t(stopHigh - _startHigh) << 32) + (stopLow - _startLow);
    }

  private:
    bool _started = false;
    uint32_t _startLow = 0, _startHigh = 0;
};

#else

struct IntervalTimer {
    explicit IntervalTimer(bool start = true) : _started(start)
    {
        if (_started) {
            _startTicks = GetStartTickTime();
        }
    }

    void Start()
    {
        _started = true;
        _startTicks = GetStartTickTime();
    }

    bool IsStarted() const { return _started; }

    uint64_t GetStartTicks() const { return _startTicks; }

    static uint64_t GetCurrentTicks() { return GetStopTickTime(); }

    uint64_t GetElapsedTicks() const
    {
        if (!_started) {
            return 0;
        }
        return GetStopTickTime() - _startTicks;
    }

  private:
    bool _started = false;
    uint64_t _startTicks;
};

#endif

/// Return the tick time resolution.  Although the number of ticks per second
/// may be very large, on many current systems the tick timers do not update at
/// that rate.  Rather, sequential calls to GetTickTime() may report
/// increases of 10s to 100s of ticks, with a minimum increment betwewen calls.
/// This function returns that minimum increment as measured at startup time.
///
/// Note that if this value is of sufficient size, then short times measured
/// with tick timers are potentially subject to significant noise.  In
/// particular, an interval of measured tick time is liable to be off by +/- one
/// GetTickQuantum().
ARCH_API
uint64_t GetTickQuantum();

/// Return the ticks taken to record an interval of time with IntervalTimer,
/// as measured at startup time.
ARCH_API
uint64_t GetIntervalTimerTickOverhead();


/// Convert a duration measured in "ticks", as returned by
/// \c GetTickTime(), to nanoseconds.
///
/// An example to test the timing routines would be:
/// \code
///     IntervalTimer iTimer;
///     sleep(10);
///
///     // duration should be approximately 10/// 1e9 = 1e10 nanoseconds.
///     int64_t duration = TicksToNanoseconds(iTimer.GetElapsedTicks());
/// \endcode
///
ARCH_API
int64_t TicksToNanoseconds(uint64_t nTicks);

/// Convert a duration measured in "ticks", as returned by
/// \c GetTickTime(), to seconds.
ARCH_API
double TicksToSeconds(uint64_t nTicks);

/// Convert a duration in seconds to "ticks", as returned by
/// \c GetTickTime().
ARCH_API
uint64_t SecondsToTicks(double seconds);

/// Get nanoseconds per tick. Useful when converting ticks obtained from
/// \c TickTime()
ARCH_API
double GetNanosecondsPerTick();

ARCH_API
uint64_t _MeasureExecutionTime(
    uint64_t maxMicroseconds, bool *reachedConsensus, void const *m,
    uint64_t (*callM)(void const *, int));

/// Run \p fn repeatedly attempting to determine a consensus fastest execution
/// time with low noise, for up to \p maxMicroseconds, then return the consensus
/// fastest execution time.  If a consensus is not reached in that time, return
/// a best estimate instead.  If \p reachedConsensus is not null, set it to
/// indicate whether or not a consensus was reached.  This function ignores \p
/// maxMicroseconds greater than 5 seconds and runs for up to 5 seconds instead.
/// The \p fn will run for an indeterminate number of times, so it should be
/// side-effect free.  Also, it should do essentially the same work on every
/// invocation so that timing its execution makes sense.
template <class Fn>
uint64_t MeasureExecutionTime(
    Fn const &fn, uint64_t maxMicroSeconds = 10000, /* 10 msec */
    bool *reachedConsensus = nullptr)
{
    auto measureN = [&fn](int nTimes) -> uint64_t {
        IntervalTimer iTimer;
        for (int i = nTimes; i--;) {
            std::atomic_signal_fence(std::memory_order_seq_cst);
            (void)fn();
            std::atomic_signal_fence(std::memory_order_seq_cst);
        }
        return iTimer.GetElapsedTicks();
    };

    using MeasureNType = decltype(measureN);

    return _MeasureExecutionTime(
        maxMicroSeconds,
        reachedConsensus,
        static_cast<void const *>(&measureN),
        [](void const *mN, int nTimes) {
            return (*static_cast<MeasureNType const *>(mN))(nTimes);
        });
}

///@}

}  // namespace arch

#endif  // ARCH_TIMING_H
