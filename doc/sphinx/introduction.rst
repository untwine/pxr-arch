.. _introduction:

************
Introduction
************

The arch library is a repository for all architecture-dependent code. It
isolates all platform dependencies (and confusing #ifdefs) into one small
library and also serves as a common area for documentation of these
multi-platform issues.

The high-level grouping of the classes/functions is:

* `Bits <./doxygen/group__group___bits.html>`_
* `Multithreading <./doxygen/group__group___multithreading.html>`_
* `Math <./doxygen/group__group___math.html>`_
* `Strings <./doxygen/group__group___strings.html>`_
* `System Functions <./doxygen/group__group___system_functions.html>`_
* `Memory Management <./doxygen/group__group___memory.html>`_
* `Diagnostics <./doxygen/group__group___diagnostics.html>`_
* `Symbol Visibility <./doxygen/group__group___symbol_visibility.html>`_

Symbols for use within ``libarch``:

For OS:

* ARCH_OS_LINUX
* ARCH_OS_DARWIN
* ARCH_OS_WINDOWS

For processor:

* ARCH_CPU_INTEL
* ARCH_CPU_ARM

For bits:

* ARCH_BITS_64

For compiler:

* ARCH_COMPILER_CLANG

    * ARCH_COMPILER_CLANG_MAJOR
    * ARCH_COMPILER_CLANG_MINOR
    * ARCH_COMPILER_CLANG_PATCHLEVEL

* ARCH_COMPILER_GCC

    * ARCH_COMPILER_GCC_MAJOR
    * ARCH_COMPILER_GCC_MINOR
    * ARCH_COMPILER_GCC_PATCHLEVEL

* ARCH_COMPILER_MSVC

    * ARCH_COMPILER_MSVC_VERSION

* ARCH_COMPILER_ICC
