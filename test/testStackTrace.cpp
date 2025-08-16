// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Modified by Jeremy Retailleau.

#include <pxr/arch/pxr.h>
#include <pxr/arch/stackTrace.h>
#include <pxr/arch/defines.h>
#include <pxr/arch/error.h>
#include <pxr/arch/fileSystem.h>
#include <pxr/arch/testArchUtil.h>

#include <string>
#include <cstdlib>

ARCH_NAMESPACE_USING_DIRECTIVE

int main(int argc, char** argv)
{
    // Verify the "is crashing" flag is initialized properly, and doesn't
    // get modified until we call the fatal process state handler below.
    ARCH_AXIOM(!ArchIsAppCrashing());

    ArchSetProgramNameForErrors( "testArch ArchError" );
    ArchTestCrashArgParse(argc, argv);

    ARCH_AXIOM(!ArchIsAppCrashing());

    std::string log = ArchMakeTmpFileName("statusLogTester");
    FILE *logFile;

    ARCH_AXIOM((logFile = ArchOpenFile(log.c_str(), "w")) != NULL);
    fputs("fake log\n", logFile);
    fputs("let's throw in a weird printf %1024$s specifier\n", logFile);
    fclose(logFile);

    ArchLogStackTrace("Crashing", true, log.c_str());
    ArchUnlinkFile(log.c_str());

    ARCH_AXIOM(!ArchIsAppCrashing());
    ArchLogCurrentProcessState("Test Non-Fatal");

    ARCH_AXIOM(!ArchIsAppCrashing());
    ArchLogFatalProcessState("Test Fatal");

    // Now we should be marked as crashing
    ARCH_AXIOM(ArchIsAppCrashing());

    // test crashing with and without spawning
    ArchTestCrash(ArchTestCrashMode::ReadInvalidAddresses);
    ArchTestCrash(ArchTestCrashMode::ReadInvalidAddressesWithThread);

    // test GetStackTrace
    std::vector<std::string> stackTrace = ArchGetStackTrace(20);
    bool found = false;
    for (unsigned int i = 0; i < stackTrace.size(); i++) {
        found |= (stackTrace[i].find("main", 0) != std::string::npos);
    }
#if defined(ARCH_OS_WINDOWS) && !defined(_DEBUG)
    // Release builds on windows can't get symbolic names.
    found |= !stackTrace.empty();
#endif
    ARCH_AXIOM(found);

    return 0;
}

