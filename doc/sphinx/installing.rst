.. _installing:

**********
Installing
**********

.. highlight:: bash

The library can be installed using :term:`CMake` (any version over `3.21
<https://cmake.org/cmake/help/latest/release/3.21.html>`_).

.. _installing/dependencies:

Dependencies
============

Custom search paths to dependent packages can be provided with the following
:term:`CMake` options (or environment variable):

============================= =========================================================
Option / Environment Variable Description
============================= =========================================================
Doxygen_ROOT                  Add search path to :term:`doxygen` program.
Sphinx_ROOT                   Add search path to :term:`sphinx-build <Sphinx>` program.
ClangFormat_ROOT              Add search path to :term:`clang-format` program.
============================= =========================================================

.. note::

    These feature is provided by :term:`CMake` under the `CMP0074
    <https://cmake.org/cmake/help/latest/policy/CMP0074.html>`_ policy

.. _installing/building:

Building library
================

Obtain a copy of the source by either downloading the
`zipball <https://github.com/untwine/arch/archive/main.zip>`_ or
cloning the public repository::

    git clone git@github.com:untwine/arch.git

Then you can build and install the library as follows::

    cd arch
    cmake -DCMAKE_INSTALL_PREFIX=/path/to/destination -S . -B ./build ..
    cmake --build ./build --target install

Here are a few :term:`CMake` options that can be used to influence the building
process:

========================== =================================================================
Option                     Description
========================== =================================================================
BUILD_TESTS                Indicate whether tests should be built. Default is true.
BUILD_DOCS                 Indicate whether documentation should be built. Default is true.
BUILD_SHARED_LIBS          Indicate whether library should be built shared. Default is true.
CMAKE_CXX_STANDARD         Indicate the C++ standard requested. Default is C++ 14.
ENABLE_PRECOMPILED_HEADERS Support pre-compiled headers. Default is false.
========================== =================================================================

The build type can be influenced by the `CMAKE_BUILD_TYPE
<https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html>`_ option or
environment variable. By default, the "Release" build type will be used.

The library can then be used by other programs or libraries via the following
:term:`Cmake` target:

* ``arch::arch``

.. _installing/clang-format:

Apply clang-format
==================

Ensure that :term:`Clang-format` is installed for applying C++ style.

Then run the program as follows::

    cmake --build ./build --target format

.. warning::

    When contributing, please run this command before committing your code.

.. _installing/documentation:

Building documentation
======================

Ensure that :term:`Doxygen` and :term:`Sphinx` with the `lowdown
<https://pypi.org/project/Lowdown/>`_ and `sphinxcontrib-doxylink
<https://pypi.org/project/sphinxcontrib-doxylink/>`_ extensions are installed.

Then build the documentation as follows::

    cmake --build ./build --target documentation

.. note::

    Documentation is automatically built with default installation, unless you
    set the ``BUILD_DOCS`` :term:`CMake` option to false.

.. _installing/test:

Running tests
=============

Ensure that :term:`GTest` is installed.

Once the library and all tests are built, you can run the tests using
:term:`Ctest` within the build folder as follows::

    ctest

You can increase the verbosity and filter in one or several tests as follows::

    ctest -VV
    ctest -R DemangleTest.Bool -VV
    ctest -R DemangleTest.* -VV

.. note::

    Tests are automatically built with default installation, unless you
    set the ``BUILD_TESTS`` :term:`CMake` option to false.
