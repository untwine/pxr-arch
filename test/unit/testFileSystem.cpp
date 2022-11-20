#include <arch/fileSystem.h>
#include <gtest/gtest.h>

#include <cstdio>

TEST(FileSystemTest, FileOperations)
{
    std::string firstName = arch::MakeTmpFileName("archFS");
    FILE *firstFile;

    char const *const testContent = "text in a file";

    // Open a file, check that its length is 0, write to it, close it, and then
    // check that its length is now the number of characters written.
    ASSERT_NE((firstFile = arch::OpenFile(firstName.c_str(), "wb")), nullptr);
    fflush(firstFile);
    ASSERT_EQ(arch::GetFileLength(firstName.c_str()), 0);
    fputs(testContent, firstFile);
    fclose(firstFile);
    ASSERT_EQ(arch::GetFileLength(firstName.c_str()), strlen(testContent));

    // Map the file and assert the bytes are what we expect they are.
    ASSERT_NE((firstFile = arch::OpenFile(firstName.c_str(), "rb")), nullptr);
    arch::ConstFileMapping cfm = arch::MapFileReadOnly(firstFile);
    fclose(firstFile);
    ASSERT_TRUE(cfm);
    ASSERT_EQ(memcmp(testContent, cfm.get(), strlen(testContent)), 0);
    cfm.reset();

    // Try again with a mutable mapping.
    ASSERT_NE((firstFile = arch::OpenFile(firstName.c_str(), "rb")), nullptr);
    arch::MutableFileMapping mfm = arch::MapFileReadWrite(firstFile);
    fclose(firstFile);
    ASSERT_TRUE(mfm);
    ASSERT_EQ(memcmp(testContent, mfm.get(), strlen(testContent)), 0);
    // Check that we can successfully mutate.
    mfm.get()[0] = 'T';
    mfm.get()[2] = 's';
    ASSERT_EQ(memcmp("Test", mfm.get(), strlen("Test")), 0);
    mfm.reset();
    ArchUnlinkFile(firstName.c_str());

    // Test PWrite and PRead.
    auto len = (int64_t)strlen(testContent);
    ASSERT_NE((firstFile = arch::OpenFile(firstName.c_str(), "w+b")), nullptr);
    ASSERT_EQ(arch::PWrite(firstFile, testContent, len, 0), len);
    std::unique_ptr<char[]> buf(new char[len]);
    ASSERT_EQ(arch::PRead(firstFile, buf.get(), len, 0), len);
    ASSERT_EQ(memcmp(testContent, buf.get(), len), 0);
    char const *const newText = "overwritten in a file";
    ASSERT_EQ(
        arch::PWrite(
            firstFile, newText, strlen(newText), 5 /*index of 'in a file'*/),
        strlen(newText));
    std::unique_ptr<char[]> buf2(new char[strlen("written in a")]);
    ASSERT_EQ(
        arch::PRead(
            firstFile,
            buf2.get(),
            strlen("written in a"),
            9 /*index of 'written in a'*/),
        strlen("written in a"));
    ASSERT_EQ(memcmp("written in a", buf2.get(), strlen("written in a")), 0);

    // create and remove a tmp subdir
    std::string retpath;
    retpath = arch::MakeTmpSubdir(arch::GetTmpDir(), "myprefix");
    ASSERT_NE(retpath, "");
    ArchRmDir(retpath.c_str());
}

TEST(FileSystemTest, NormPath)
{
    ASSERT_EQ(arch::NormPath(""), ".");
    ASSERT_EQ(arch::NormPath("."), ".");
    ASSERT_EQ(arch::NormPath(".."), "..");
    ASSERT_EQ(arch::NormPath("foobar/../barbaz"), "barbaz");
    ASSERT_EQ(arch::NormPath("/"), "/");
    ASSERT_EQ(arch::NormPath("//"), "//");
    ASSERT_EQ(arch::NormPath("///"), "/");
    ASSERT_EQ(arch::NormPath("///foo/.//bar//"), "/foo/bar");
    ASSERT_EQ(arch::NormPath("///foo/.//bar//.//..//.//baz"), "/foo/baz");
    ASSERT_EQ(arch::NormPath("///..//./foo/.//bar"), "/foo/bar");
    ASSERT_EQ(
        arch::NormPath("foo/bar/../../../../../../baz"), "../../../../baz");

#if defined(ARCH_OS_WINDOWS)
    ASSERT_EQ(arch::NormPath("C:\\foo\\bar"), "c:/foo/bar");
    ASSERT_EQ(arch::NormPath("C:foo\\bar"), "c:foo/bar");
    ASSERT_EQ(
        arch::NormPath("C:\\foo\\bar", /* stripDriveSpecifier = */ true),
        "/foo/bar");
    ASSERT_EQ(
        arch::NormPath("C:foo\\bar", /* stripDriveSpecifier = */ true),
        "foo/bar");
#endif
}

TEST(FileSystemTest, AbsPath)
{
    ASSERT_EQ(arch::AbsPath(""), "");
    ASSERT_NE(arch::AbsPath("foo"), "foo");

    auto path1 = arch::AbsPath("/foo/bar");
    auto path2 = arch::AbsPath("/foo/bar/../baz");

#if defined(ARCH_OS_WINDOWS)
    // Strip drive specifier and convert backslashes to forward slashes.
    std::string _path1 = path1.substr(2);
    std::replace(_path1.begin(), _path1.end(), '\\', '/');
    ASSERT_EQ(_path1, "/foo/bar");

    std::string _path2 = path2.substr(2);
    std::replace(_path2.begin(), _path2.end(), '\\', '/');
    ASSERT_EQ(_path2, "/foo/baz");
#else
    ASSERT_EQ(path1, "/foo/bar");
    ASSERT_EQ(path2, "/foo/baz");
#endif
}
