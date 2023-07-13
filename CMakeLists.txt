cmake_minimum_required(VERSION 3.21...3.25)

# Default build type value.
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type")

project(arch
    VERSION 0.3.2
    HOMEPAGE_URL "https://github.com/untwine/arch"
    LANGUAGES CXX
)

include(GNUInstallDirs)

if (NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 14 CACHE STRING "Default C++ standard")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default options.
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" ON)
option(BUILD_SHARED_LIBS "Build Shared Library" ON)
option(ENABLE_PRECOMPILED_HEADERS "Enable precompiled headers." OFF)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

    # Make sure WinDef.h does not define min and max macros which
    # will conflict with std::min() and std::max().
    add_definitions(-DNOMINMAX)

    # Exclude headers from unnecessary Windows APIs to improve build
    # times and avoid annoying conflicts with macros defined in those
    # headers.
    add_definitions(-DWIN32_LEAN_AND_MEAN)

    # The /Zc:inline option strips out the "arch_ctor_<name>" symbols used for
    # library initialization by ARCH_CONSTRUCTOR starting in Visual Studio 2019,
    # causing release builds to fail. Disable the option for this and later
    # versions.
    #
    # For more details, see:
    # https://developercommunity.visualstudio.com/content/problem/914943/zcinline-removes-extern-symbols-inside-anonymous-n.html
    if (MSVC_VERSION GREATER_EQUAL 1920)
        set(CMAKE_CXX_FLAGS "/Zc:inline- ${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "/Zc:inline ${CMAKE_CXX_FLAGS}")
    endif()
endif()

# Update build type from environment for CMake < 3.22
if (DEFINED ENV{CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE}
        CACHE STRING "Specifies the build type" FORCE)
endif()

# Discover custom module finders.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

# Silence "Up-to-date:" install messages
set(CMAKE_INSTALL_MESSAGE NEVER)

# Generate "compile_commands.json" for use by editors and other developer tools.
# https://cmake.org/cmake/help/v3.5/variable/CMAKE_EXPORT_COMPILE_COMMANDS.html
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(Threads REQUIRED)

add_subdirectory(src)

# Build and setup tests if required.
if (BUILD_TESTS)
    find_package(GTest REQUIRED)
    include(GoogleTest)

    enable_testing()

    add_subdirectory(test)
endif()

# Build documentation if required.
if (BUILD_DOCS)
    find_package(Sphinx 1.8.6 REQUIRED)
    find_package(Doxygen 1.8.5 REQUIRED)

    add_subdirectory(doc)
endif()

# Add format target if clang-format is found.
find_package(ClangFormat 7)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "cmake/arch-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/arch-config.cmake"
    INSTALL_DESTINATION share/cmake/arch
)

write_basic_package_version_file(
    "arch-config-version.cmake"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/arch-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/arch-config-version.cmake"
    DESTINATION share/cmake/arch
)
