#include <arch/symbols.h>
#include <gtest/gtest.h>

#include <cstdlib>

static void Code() {}
static int data = 1;
static int bss;

static bool _GetLibraryPath(void* address, std::string* result)
{
    return arch::GetAddressInfo(address, result, nullptr, nullptr, nullptr);
}

static std::string GetBasename(const std::string& path)
{
#if defined(ARCH_OS_WINDOWS)
    std::string::size_type i = path.find_last_of("/\\");
    if (i != std::string::npos) {
        std::string::size_type j = path.find(".exe");
        if (j != std::string::npos) {
            return path.substr(i + 1, j - i - 1);
        }
        return path.substr(i + 1);
    }
#else
    std::string::size_type i = path.rfind('/');
    if (i != std::string::npos) {
        return path.substr(i + 1);
    }
#endif
    return path;
}

TEST(SymbolsTest, GetAddressInfo)
{
    std::string path;

    // Invalid pointer.
    ASSERT_FALSE(_GetLibraryPath(nullptr, &path));

    // Pointer to a local non-function.
    ASSERT_FALSE(_GetLibraryPath(&path, &path));

    // Pointer into the DATA section.
    ASSERT_TRUE(_GetLibraryPath(&data, &path));
    ASSERT_EQ(GetBasename(path), "testArchSymbols");

    // Pointer into the BSS section.
    ASSERT_TRUE(_GetLibraryPath(&bss, &path));
    ASSERT_EQ(GetBasename(path), "testArchSymbols");

    // Find this library.
    ASSERT_TRUE(_GetLibraryPath((void*)&Code, &path));
    ASSERT_EQ(GetBasename(path), "testArchSymbols");

    // Find another library.
    ASSERT_TRUE(_GetLibraryPath((void*)&exit, &path));
    ASSERT_NE(GetBasename(path), "testArchSymbols");
}
