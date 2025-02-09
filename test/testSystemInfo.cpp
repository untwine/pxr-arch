// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#include <pxr/arch/pxr.h>
#include <pxr/arch/systemInfo.h>
#include <pxr/arch/error.h>

ARCH_NAMESPACE_USING_DIRECTIVE

using std::string;

//most of these tests are just for code coverage
int main(int /*argc*/, char const** /*argv*/)
{
    ARCH_AXIOM(ArchGetExecutablePath().find("testArch", 0) != string::npos);
    return 0;
}

