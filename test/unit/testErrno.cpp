#include <arch/errno.h>
#include <gtest/gtest.h>

TEST(ErrnoTest, ErrorMessages)
{
    for (int i = -1; i < 10; i++) {
        ASSERT_NE(arch::StrError(i), "");
    }
}
