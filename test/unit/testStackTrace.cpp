// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
// Modified by Jeremy Retailleau.

#include <pxr/arch/fileSystem.h>
#include <pxr/arch/stackTrace.h>
#include <archTest/util.h>
#include <gtest/gtest.h>

#include <cstdio>
#include <string>

using namespace pxr;

TEST(StackTraceTest, TestCrash)
{
    ASSERT_FALSE(arch::IsAppCrashing());

    std::string log = arch::MakeTmpFileName("statusLogTester");
    FILE *logFile;

    ASSERT_NE((logFile = arch::OpenFile(log.c_str(), "w")), nullptr);
    fputs("fake log\n", logFile);
    fputs("let's throw in a weird printf %1024$s specifier\n", logFile);
    fclose(logFile);

    arch::LogStackTrace("Crashing", true, log.c_str());
    arch::UnlinkFile(log.c_str());

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
