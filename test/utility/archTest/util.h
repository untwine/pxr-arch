#ifndef ARCH_TEST_UTIL_H
#define ARCH_TEST_UTIL_H

namespace archTest {

// Crash types.
enum class CrashMode {
    Error,
    ReadInvalidAddresses,
    ReadInvalidAddressesWithThread
};

// Cause the test to crash deliberately.
void Crash(CrashMode mode);

// On Windows we can't easily fork() so we just run the test again with
// command line arguments to request a crash.
void CrashArgParse(int argc, char** argv);

}  // namespace archTest

#endif  // ARCH_TEST_UTIL_H
