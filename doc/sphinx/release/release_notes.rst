.. _release/release_notes:

*************
Release Notes
*************

.. release:: Upcoming

    .. change:: changed

        Synced library with the ``arch`` module within USD v23.05.

.. release:: 0.2.0
    :date: 2023-07-05

    .. change:: new

        Added automatic tests on Linux, MacOS and Windows.

    .. change:: new

        Added ``ENABLE_PRECOMPILED_HEADERS`` :term:`CMake` option to support
        pre-compiled headers.

        .. seealso:: :ref:`installing/building`

    .. change:: change

        Raised :term:`CMake` minimum version to 3.21 as it is required for 
        using `TARGET_RUNTIME_DLLS 
        <https://cmake.org/cmake/help/v3.21/manual/cmake-generator-expressions.7.html#genex:TARGET_RUNTIME_DLLS>`_ 
        generator expression for running the tests on Windows.

    .. change:: changed

        Replaced the following macros in the :file:`arch/fileSystem.h` header 
        with function aliases using `static constexpr 
        <https://en.cppreference.com/w/cpp/language/constexpr>`_ to ensure that
        the ``arch::`` namespace is used consistently throughout the library:

        * ``ArchChmod`` →  ``arch::Chmod``
        * ``ArchCloseFile`` →  ``arch::CloseFile``
        * ``ArchUnlinkFile`` →  ``arch::UnlinkFile``
        * ``ArchFileAccess`` →  ``arch::FileAccess``
        * ``ArchFdOpen`` →  ``arch::FdOpen``
        * ``ArchFileNo`` →  ``arch::FileNo``
        * ``ArchFileIsaTTY`` →  ``arch::FileIsaTTY``
        * ``ArchRmDir`` →  ``arch::RmDir``

    .. change:: fixed

        Ensured that the `CMAKE_CXX_STANDARD 
        <https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html>`_ 
        variable can be set to override the default C++ standard for all 
        targets.

    .. change:: fixed

        Fixed compatibility issues with Windows.

.. release:: 0.1.0
    :date: 2022-11-19

    .. change:: new

        Initial release based on the state of the ``arch`` module within
        USD v22.11.
