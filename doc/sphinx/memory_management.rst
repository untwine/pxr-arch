.. _memory_management:

*****************
Memory Management
*****************

Functions having to do with memory allocation/handling

.. _memory_management/files:

Files
~~~~~

* :arch-cpp:`align.h`
* :arch-cpp:`mallocHook.h`

.. _memory_management/classes:

Classes
~~~~~~~

* :arch-cpp:`arch::MallocHook`

.. _memory_management/macros:

Macros
~~~~~~

* :arch-cpp:`ARCH_MAX_ALIGNMENT_INCREASE`
* :arch-cpp:`ARCH_CACHE_LINE_SIZE`

.. _memory_management/functions:

Functions
~~~~~~~~~

* :arch-cpp:`arch::AlignMemorySize`
* :arch-cpp:`arch::AlignMemory`
* :arch-cpp:`arch::AlignedAlloc`
* :arch-cpp:`arch::AlignedFree`
* :arch-cpp:`arch::IsPtmallocActive`
* :arch-cpp:`arch::IsStlAllocatorOff`
