#include <arch/export.h>
#include <archTest/abi.h>

extern "C" {

ARCH_EXPORT archTest::AbiBase2* newDerived()
{
    return new archTest::AbiDerived<int>;
}
}
