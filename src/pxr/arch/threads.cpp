// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#include "./threads.h"

#include <thread>

namespace pxr {

// Static initializer to get the main thread id.  We want this to run as early
// as possible, so we actually capture the main thread's id.  We assume that
// we're not starting threads before main().

namespace {

const std::thread::id _mainThreadId = std::this_thread::get_id();

} // anonymous namespace

bool ArchIsMainThread()
{
    return std::this_thread::get_id() == _mainThreadId;
}

std::thread::id
ArchGetMainThreadId()
{
    return _mainThreadId;
}

}  // namespace pxr