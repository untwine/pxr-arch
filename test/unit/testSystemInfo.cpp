#include <arch/systemInfo.h>
#include <gtest/gtest.h>

#include <string>

TEST(SystemInfoTest, GetExecutablePath)
{
    ASSERT_NE(arch::GetExecutablePath().find("testArch", 0), std::string::npos);
}
