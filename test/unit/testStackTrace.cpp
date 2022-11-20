#include <arch/fileSystem.h>
#include <arch/stackTrace.h>
#include <archTest/util.h>
#include <gtest/gtest.h>

#include <cstdio>
#include <string>

TEST(StackTraceTest, TestCrash)
{
    ASSERT_FALSE(arch::IsAppCrashing());

    std::string log = arch::MakeTmpFileName("statusLogTester");
    FILE* logFile;

    ASSERT_NE((logFile = arch::OpenFile(log.c_str(), "w")), nullptr);
    fputs("fake log\n", logFile);
    fputs("let's throw in a weird printf %1024$s specifier\n", logFile);
    fclose(logFile);

    arch::LogStackTrace("Crashing", true, log.c_str());
    ArchUnlinkFile(log.c_str());

    ASSERT_FALSE(arch::IsAppCrashing());
    arch::LogCurrentProcessState("Test Non-Fatal");

    ASSERT_FALSE(arch::IsAppCrashing());
    arch::LogFatalProcessState("Test Fatal");

    // Now we should be marked as crashing
    ASSERT_TRUE(arch::IsAppCrashing());

    // test crashing with and without spawning
    archTest::Crash(archTest::CrashMode::ReadInvalidAddresses);
    archTest::Crash(archTest::CrashMode::ReadInvalidAddressesWithThread);

    // test GetStackTrace
    std::vector<std::string> stackTrace = arch::GetStackTrace(20);
    bool found = false;
    for (unsigned int i = 0; i < stackTrace.size(); i++) {
        found |= (stackTrace[i].find("main", 0) != std::string::npos);
    }
#if defined(ARCH_OS_WINDOWS) && !defined(_DEBUG)
    // Release builds on windows can't get symbolic names.
    found |= !stackTrace.empty();
#endif
    ASSERT_TRUE(found);
}

int main(int argc, char** argv)
{
    arch::SetProgramNameForErrors("testArch ArchError");
    archTest::CrashArgParse(argc, argv);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
