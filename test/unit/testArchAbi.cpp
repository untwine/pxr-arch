#include <arch/library.h>
#include <arch/systemInfo.h>
#include <archTest/abi.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <string>

TEST(ArchABITest, GetExecutablePath)
{
    std::string path = arch::GetExecutablePath();
    std::string root = std::getenv("EXE_PATH");
#if defined(ARCH_OS_WINDOWS)
    std::string expected = root + "\testArchAbi";
#else
    std::string expected = root + "/testArchAbi";
#endif
    ASSERT_EQ(path, expected);
}

TEST(ArchABITest, Library)
{
    std::string path = std::getenv("PLUGIN_PATH");
#if defined(ARCH_OS_WINDOWS)
    path += "\\libarchTestPlugin.dll";
#elif defined(ARCH_OS_DARWIN)
    path += "/libarchTestPlugin.dylib";
#else
    path += "/libarchTestPlugin.so";
#endif
    auto plugin = arch::LibraryOpen(path, ARCH_LIBRARY_LAZY);
    ASSERT_NE(plugin, nullptr);
    ASSERT_EQ(arch::LibraryError(), "");

    // Get symbol from library.
    using NewDerived = archTest::AbiBase2* (*)();
    auto newPluginDerived =
        (NewDerived)arch::LibraryGetSymbolAddress(plugin, "newDerived");
    ASSERT_NE(newPluginDerived, nullptr);

    // Fail to get symbol from library.
    auto symbol =
        (NewDerived)arch::LibraryGetSymbolAddress(plugin, "incorrect");
    ASSERT_EQ(symbol, nullptr);

    // Create a derived object in this executable and in the plugin.
    archTest::AbiBase2* mainDerived = new archTest::AbiDerived<int>;
    archTest::AbiBase2* pluginDerived = newPluginDerived();

    // The types should be equal and the dynamic cast should not
    // change the pointer.
    ASSERT_EQ(typeid(*mainDerived), typeid(*pluginDerived));
    ASSERT_EQ(
        pluginDerived, dynamic_cast<archTest::AbiDerived<int>*>(pluginDerived));

    auto status = arch::LibraryClose(plugin);
    ASSERT_EQ(status, 0);
}

TEST(ArchABITest, LibraryOpenError)
{
    std::string path = "/incorrect";
    auto plugin = arch::LibraryOpen(path, ARCH_LIBRARY_LAZY);
    ASSERT_EQ(plugin, nullptr);
    ASSERT_NE(arch::LibraryError(), "");
}
