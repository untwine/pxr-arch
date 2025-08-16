// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#include <pxr/arch/export.h>
#include <pxr/arch/pxr.h>
#include <pxr/arch/testArchAbi.h>


ARCH_NAMESPACE_USING_DIRECTIVE

extern "C" {

ARCH_EXPORT ArchAbiBase2* newDerived() { return new ArchAbiDerived<int>; }

}
