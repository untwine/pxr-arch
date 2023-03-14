.. _release/release_notes:

*************
Release Notes
*************

.. release:: Upcoming

    .. change:: changed

        Replace the following macros in :file:`arch/fileSystem.h` header with 
        ``static constexpr`` function variables so that it can be consistently 
        namespaced:

        * ``ArchChmod`` →  ``arch::Chmod``
        * ``ArchCloseFile`` →  ``arch::CloseFile``
        * ``ArchUnlinkFile`` →  ``arch::UnlinkFile``
        * ``ArchFileAccess`` →  ``arch::FileAccess``
        * ``ArchFdOpen`` →  ``arch::FdOpen``
        * ``ArchFileNo`` →  ``arch::FileNo``
        * ``ArchFileIsaTTY`` →  ``arch::FileIsaTTY``
        * ``ArchRmDir`` →  ``arch::RmDir``

.. release:: 0.1.0
    :date: 2022-11-19

    .. change:: new

        Initial release based on the state of the ``arch`` module within
        USD v22.11.
