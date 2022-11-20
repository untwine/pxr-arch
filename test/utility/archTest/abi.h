#ifndef ARCH_TEST_ABI_H
#define ARCH_TEST_ABI_H

#include "arch/api.h"

namespace archTest {

struct AbiBase1 {
    void* dummy;
};

struct AbiBase2 {
    virtual ~AbiBase2() = default;
    virtual const char* name() const = 0;
};

template <class T>
struct AbiDerived : public AbiBase1, public AbiBase2 {
    AbiDerived() : AbiBase1(), AbiBase2() {}
    ~AbiDerived() override = default;
    const char* name() const override { return "AbiDerived"; }
};

}  // namespace archTest

#endif  // ARCH_TEST_ABI_H
