// Copyright 2022 Pixar
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
// Modified by Jeremy Retailleau

#ifndef ARCH_FILE_SYSTEM_H
#define ARCH_FILE_SYSTEM_H

/// \file arch/fileSystem.h
/// \ingroup group_SystemFunctions
/// Architecture dependent file system access

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cstdio>
#include <memory>
#include <set>
#include <string>

#include "arch/api.h"
#include "arch/defines.h"
#include "arch/inttypes.h"

#if defined(ARCH_OS_LINUX)
#include <glob.h>
#include <sys/statfs.h>
#include <unistd.h>
#elif defined(ARCH_OS_DARWIN)
#include <glob.h>
#include <sys/mount.h>
#include <unistd.h>
#elif defined(ARCH_OS_WINDOWS)
#include <windows.h>
#include <io.h>
#include <stringapiset.h>
#endif

namespace arch {

/// \addtogroup group_SystemFunctions
///@{
#if !defined(ARCH_OS_WINDOWS)
#ifdef _POSIX_VERSION
#include <climits> /* for PATH_MAX */
#else
#include <sys/param.h> /* for MAXPATHLEN */
#endif
#else
// XXX -- Should probably have ARCH_ macro for this.
#define S_ISDIR(m) (((m)&S_IFMT) == S_IFDIR)

// See https://msdn.microsoft.com/en-us/library/1w06ktdy.aspx
// See https://msdn.microsoft.com/en-us/library/1w06ktdy.aspx
// XXX -- Should probably have Arch enum for these.
#define F_OK 0  // Test for existence.
#define X_OK 1  // Test for execute permission.
#define W_OK 2  // Test for write permission.
#define R_OK 4  // Test for read permission.
#endif

#if defined(ARCH_OS_WINDOWS)
#define ARCH_GLOB_NOCHECK 1
#define ARCH_GLOB_MARK 2
#define ARCH_GLOB_NOSORT 4
#else
#define ARCH_GLOB_NOCHECK GLOB_NOCHECK
#define ARCH_GLOB_MARK GLOB_MARK
#define ARCH_GLOB_NOSORT GLOB_NOSORT
#endif
#define ARCH_GLOB_DEFAULT (ARCH_GLOB_NOCHECK | ARCH_GLOB_MARK)

#ifndef ARCH_PATH_MAX
#ifdef PATH_MAX
#define ARCH_PATH_MAX PATH_MAX
#else
#ifdef MAXPATHLEN
#define ARCH_PATH_MAX MAXPATHLEN
#else
#ifdef _MAX_PATH
#define ARCH_PATH_MAX _MAX_PATH
#else
#define ARCH_PATH_MAX 1024
#endif
#endif
#endif
#endif

#if defined(ARCH_OS_WINDOWS)
#define ARCH_PATH_SEP "\\"
#define ARCH_PATH_LIST_SEP ";"
#define ARCH_REL_PATH_IDENT ".\\"
#else
#define ARCH_PATH_SEP "/"
#define ARCH_PATH_LIST_SEP ":"
#define ARCH_REL_PATH_IDENT "./"
#endif

#if defined(ARCH_OS_WINDOWS)
typedef struct __stat64 StatType;
#else
typedef struct stat StatType;
#endif

/// \file fileSystem.h
/// Architecture dependent file system access
/// \ingroup group_SystemFunctions
///

/// Opens a file.
///
/// Opens the file that is specified by filename.
/// Returning true if the file was opened successfully; false otherwise.
///
ARCH_API FILE *OpenFile(char const *fileName, char const *mode);

#if defined(ARCH_OS_WINDOWS)
static constexpr auto Chmod = _chmod;
#else
static constexpr auto Chmod = chmod;
#endif

#if defined(ARCH_OS_WINDOWS)
static constexpr auto CloseFile = _close;
#else
static constexpr auto CloseFile = close;
#endif

#if defined(ARCH_OS_WINDOWS)
static constexpr auto UnlinkFile = _unlink;
#else
static constexpr auto UnlinkFile = unlink;
#endif

#if defined(ARCH_OS_WINDOWS)
ARCH_API int FileAccess(const char *path, int mode);
#else
static constexpr auto FileAccess = access;
#endif

#if defined(ARCH_OS_WINDOWS)
static constexpr auto FdOpen = _fdopen;
#else
static constexpr auto FdOpen = fdopen;
#endif

#if defined(ARCH_OS_WINDOWS)
static constexpr auto FileNo = _fileno;
#else
static constexpr auto FileNo = fileno;
#endif

#if defined(ARCH_OS_WINDOWS)
static constexpr auto FileIsaTTY = _isatty;
#else
static constexpr auto FileIsaTTY = isatty;
#endif

#if defined(ARCH_OS_WINDOWS)
ARCH_API int RmDir(const char *path);
#else
static constexpr auto RmDir = rmdir;
#endif

/// Return the length of a file in bytes.
///
/// Returns -1 if the file cannot be opened/read.
ARCH_API int64_t GetFileLength(const char *fileName);
ARCH_API int64_t GetFileLength(FILE *file);

/// Return a filename for this file, if one can be obtained. Note that there
/// are many reasons why it may be impossible to obtain a filename, even for an
/// opened FILE *. Whenever possible avoid using this function and instead
/// store the filename for future use.
ARCH_API std::string GetFileName(FILE *file);

/// Returns true if the data in \c stat struct \p st indicates that the target
/// file or directory is writable.
///
/// This returns true if the struct pointer is valid, and the stat indicates
/// the target is writable by the effective user, effective group, or all
/// users.
ARCH_API bool StatIsWritable(const StatType *st);

/// Returns the modification time (mtime) in seconds for a file.
///
/// This function stores the modification time with as much precision as is
/// available in the stat structure for the current platform in \p time and
/// returns \c true on success, otherwise just returns \c false.
ARCH_API bool GetModificationTime(const char *pathname, double *time);

/// Returns the modification time (mtime) in seconds from the stat struct.
///
/// This function returns the modification time with as much precision as is
/// available in the stat structure for the current platform.
ARCH_API double GetModificationTime(const StatType &st);

/// Normalizes the specified path, eliminating double slashes, etc.
///
/// This canonicalizes paths, removing any double slashes, and eliminiating
/// '.', and '..' components of the path.  This emulates the behavior of
/// os.path.normpath in Python.
///
/// On Windows, all backslashes are converted to forward slashes and drive
/// specifiers (e.g., "C:") are lower-cased. If \p stripDriveSpecifier
/// is \c true, these drive specifiers are removed from the path.
ARCH_API std::string NormPath(
    const std::string &path, bool stripDriveSpecifier = false);

/// Returns the canonical absolute path of the specified filename.
///
/// This makes the specified path absolute, by prepending the current working
/// directory.  If the path is already absolute, it is returned unmodified.
ARCH_API std::string AbsPath(const std::string &path);

/// Returns the permissions mode (mode_t) for the given pathname.
///
/// This function stats the given pathname and returns the permissions flags
/// for it and returns true.  If the stat fails, returns false.
///
ARCH_API bool GetStatMode(const char *pathname, int *mode);

/// Return the path to a temporary directory for this platform.
///
/// The returned temporary directory will be a location that will normally
/// be cleaned out on a reboot. This is /var/tmp on Linux machines (for
/// legacy reasons), but /tmp on Darwin machines (/var/tmp on Darwin is
/// specified as a location where files are kept between system reboots -
/// see "man hier"). The returned string will not have a trailing slash.
///
/// This routine is threadsafe and will not perform any memory allocations.
ARCH_API const char *GetTmpDir();

/// Make a temporary file name, in a system-determined temporary directory.
///
/// The result returned has the form TMPDIR/prefix.pid[.n]suffix where TMPDIR
/// is a system-determined temporary directory (typically /tmp or /usr/tmp),
/// pid is the process id of the process, and the optional .n records the
/// number of times this function has been called by a process (and is ommited
/// the first time this function is called).
///
/// The call is threadsafe.
///
/// \warning This call opens a security hole because of the race between
/// choosing the name and opening the file.  This call should be avoided in
/// favor of \c MakeTmpFile().
ARCH_API
std::string MakeTmpFileName(
    const std::string &prefix, const std::string &suffix = std::string());

/// Create a temporary file, in a system-determined temporary directory.
///
/// The result returned has the form TMPDIR/prefix.XXXXXX where TMPDIR is a
/// system-determined temporary directory (typically /tmp or /usr/tmp) and
/// XXXXXX is a unique suffix.  Returns the file descriptor of the new file
/// and, if pathname isn't NULL, returns the full path to the file in
/// pathname.  Returns -1 on failure and errno is set.
///
/// The call is threadsafe.
ARCH_API
int MakeTmpFile(const std::string &prefix, std::string *pathname = nullptr);

/// Create a temporary file, in a given temporary directory.
///
/// The result returned has the form TMPDIR/prefix.XXXXXX where TMPDIR is the
/// given temporary directory and XXXXXX is a unique suffix.  Returns the file
/// descriptor of the new file and, if pathname isn't NULL, returns the full
/// path to the file in pathname.  Returns -1 on failure and errno is set.
///
/// The call is threadsafe.
ARCH_API
int MakeTmpFile(
    const std::string &tmpdir, const std::string &prefix,
    std::string *pathname = nullptr);

/// Create a temporary sub-direcrory, in a given temporary directory.
///
/// The result returned has the form TMPDIR/prefix.XXXXXX/ where TMPDIR is the
/// given temporary directory and XXXXXX is a unique suffix.  Returns the the
/// full path to the subdir in pathname.  Returns empty string on failure and
/// errno is set.
///
/// The call is threadsafe.
ARCH_API
std::string MakeTmpSubdir(const std::string &tmpdir, const std::string &prefix);

// Helper 'deleter' for use with std::unique_ptr for file mappings.
struct _Unmapper {
    _Unmapper() : _length(~0) {}
    explicit _Unmapper(size_t length) : _length(length) {}
    ARCH_API void operator()(char *mapStart) const;
    ARCH_API void operator()(char const *mapStart) const;
    size_t GetLength() const { return _length; }

  private:
    size_t _length;
};

/// ConstFileMapping and MutableFileMapping are std::unique_ptr<char
/// const *, ...> and std::unique_ptr<char *, ...> respectively.  The functions
/// MapFileReadOnly() and MapFileReadWrite() return them and provide
/// access to memory-mapped file contents.
using ConstFileMapping = std::unique_ptr<char const, _Unmapper>;
using MutableFileMapping = std::unique_ptr<char, _Unmapper>;

/// Return the length of an ConstFileMapping.
inline size_t GetFileMappingLength(ConstFileMapping const &m)
{
    return m.get_deleter().GetLength();
}

/// Return the length of an MutableFileMapping.
inline size_t GetFileMappingLength(MutableFileMapping const &m)
{
    return m.get_deleter().GetLength();
}

/// Privately map the passed \p file into memory and return a unique_ptr to the
/// read-only mapped contents.  The contents may not be modified.  If mapping
/// fails, return a null unique_ptr and if errMsg is not null fill it with
/// information about the failure.
ARCH_API
ConstFileMapping MapFileReadOnly(FILE *file, std::string *errMsg = nullptr);

/// \overload
ARCH_API
ConstFileMapping MapFileReadOnly(
    std::string const &path, std::string *errMsg = nullptr);

/// Privately map the passed \p file into memory and return a unique_ptr to the
/// copy-on-write mapped contents.  If modified, the affected pages are
/// dissociated from the underlying file and become backed by the system's swap
/// or page-file storage.  Edits are not carried through to the underlying file.
/// If mapping fails, return a null unique_ptr and if errMsg is not null fill it
/// with information about the failure.
ARCH_API
MutableFileMapping MapFileReadWrite(FILE *file, std::string *errMsg = nullptr);

/// \overload
ARCH_API
MutableFileMapping MapFileReadWrite(
    std::string const &path, std::string *errMsg = nullptr);

enum MemAdvice {
    MemAdviceNormal,        // Treat range with default behavior.
    MemAdviceWillNeed,      // OS may prefetch this range.
    MemAdviceDontNeed,      // OS may free resources related to this range.
    MemAdviceRandomAccess,  // Prefetching may not be beneficial.
};

/// Advise the OS regarding how the application intends to access a range of
/// memory.  See MemAdvice.  This is primarily useful for mapped file
/// regions.  This call does not change program semantics.  It is only an
/// optimization hint to the OS, and may be a no-op on some systems.
ARCH_API
void MemAdvise(void const *addr, size_t len, MemAdvice adv);

/// Report whether or not the mapped virtual memory pages starting at \p addr
/// for \p len bytes are resident in RAM.  Pages that are resident will not,
/// when accessed, cause a page fault while those that are not will.  Return
/// true on success and false in case of an error.  The \p addr argument must be
/// a multiple of GetPageSize().  The \p len argument need not be a multiple
/// of the page size; it will be rounded up to the next page boundary.  Fill
/// \p pageMap with 0s for pages not resident in memory and 1s for pages that
/// are. The \p pageMap argument must therefore point to at least (\p len +
/// GetPageSize()-1)/GetPageSize() bytes.
///
/// Note that currently this function is only implemented on Linux and Darwin.
/// On Windows it currently always returns false.
ARCH_API
bool QueryMappedMemoryResidency(
    void const *addr, size_t len, unsigned char *pageMap);

/// Read up to \p count bytes from \p offset in \p file into \p buffer.  The
/// file position indicator for \p file is not changed.  Return the number of
/// bytes read, or zero if at end of file.  Return -1 in case of an error, with
/// errno set appropriately.
ARCH_API
int64_t PRead(FILE *file, void *buffer, size_t count, int64_t offset);

/// Write up to \p count bytes from \p buffer to \p file at \p offset.  The file
/// position indicator for \p file is not changed.  Return the number of bytes
/// written, possibly zero if none written.  Return -1 in case of an error, with
/// errno set appropriately.
ARCH_API
int64_t PWrite(FILE *file, void const *bytes, size_t count, int64_t offset);

/// Returns the value of the symbolic link at \p path.  Returns the empty
/// string on error or if \p path does not refer to a symbolic link.
ARCH_API
std::string ReadLink(const char *path);

enum FileAdvice {
    FileAdviceNormal,        // Treat range with default behavior.
    FileAdviceWillNeed,      // OS may prefetch this range.
    FileAdviceDontNeed,      // OS may free resources related to this range.
    FileAdviceRandomAccess,  // Prefetching may not be beneficial.
};

/// Advise the OS regarding how the application intends to access a range of
/// bytes in a file.  See FileAdvice.  This call does not change program
/// semantics.  It is only an optimization hint to the OS, and may be a no-op on
/// some systems.
ARCH_API
void FileAdvise(FILE *file, int64_t offset, size_t count, FileAdvice adv);

#if defined(ARCH_OS_WINDOWS)

/// Converts UTF-16 windows string to regular std::string - Windows-only
inline std::string WindowsUtf16ToUtf8(const std::wstring &wstr)
{
    if (wstr.empty()) return std::string();
    // first call is only to get required size for string
    int size = WideCharToMultiByte(
        CP_UTF8,
        0,
        wstr.data(),
        (int)wstr.size(),
        nullptr,
        0,
        nullptr,
        nullptr);
    if (size == 0) return std::string();
    std::string str(size, 0);
    if (WideCharToMultiByte(
            CP_UTF8,
            0,
            wstr.data(),
            (int)wstr.size(),
            &str[0],
            size,
            nullptr,
            nullptr)
        == 0) {
        return std::string();
    }
    return str;
}

/// Converts regular std::string to UTF-16 windows string - Windows-only
inline std::wstring WindowsUtf8ToUtf16(const std::string &str)
{
    if (str.empty()) return std::wstring();
    // first call is only to get required size for wstring
    int size = MultiByteToWideChar(
        CP_UTF8, 0, str.data(), (int)str.size(), nullptr, 0);
    if (size == 0) return std::wstring();
    std::wstring wstr(size, 0);
    if (MultiByteToWideChar(
            CP_UTF8, 0, str.data(), (int)str.size(), &wstr[0], size)
        == 0) {
        return std::wstring();
    }
    return wstr;
}

#endif

///@}

}  // namespace arch

#endif  // ARCH_FILE_SYSTEM_H
