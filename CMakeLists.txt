cmake_minimum_required(VERSION 3.20)

# Default build type value.
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type")

project(arch
    VERSION 0.1.0
    HOMEPAGE_URL "https://github.com/Untwine/arch"
    LANGUAGES CXX
)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 14 CACHE STRING "Default C++ standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default options.
option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" ON)
option(BUILD_SHARED_LIBS "Build Shared Library" ON)

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
    "cmake/archConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/archConfig.cmake"
    INSTALL_DESTINATION share/cmake/arch
)

write_basic_package_version_file(
    "archConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/archConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/archConfigVersion.cmake"
    DESTINATION share/cmake/arch
)
