// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#include <pxr/arch/pxr.h>
#include <pxr/arch/errno.h>
#include <pxr/arch/error.h>

#include <cstdio>

ARCH_NAMESPACE_USING_DIRECTIVE

int main(int /*argc*/, char** /*argv*/)
{
    for (int i = -1; i < 10; i++) {
        const std::string msg = ArchStrerror(i);
        ARCH_AXIOM(!msg.empty());
        printf("%d -> '%s'\n", i, msg.c_str());
    }

    return 0;
}
