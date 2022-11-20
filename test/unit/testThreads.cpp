#include <arch/threads.h>
#include <gtest/gtest.h>

TEST(ThreadTest, IsMainThread) { ASSERT_TRUE(arch::IsMainThread()); }
