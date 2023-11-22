// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Written by dhl (10 Jul 2006)
//
// Modified by Jeremy Retailleau.

#include <pxr/arch/pxr.h>
#include <pxr/arch/error.h>
#include "./testArchUtil.h"

ARCH_NAMESPACE_USING_DIRECTIVE

int main(int argc, char** argv)
{
    ArchTestCrashArgParse(argc, argv);
    ArchTestCrash(ArchTestCrashMode::Error);
}
