.. _system_functions:

****************
System Functions
****************

Functions that encapsulate differing low-level system calls.

.. _system_functions/files:

Files
~~~~~

* :arch-cpp:`errno.h`
* :arch-cpp:`fileSystem.h`
* :arch-cpp:`systemInfo.h`
* :arch-cpp:`timing.h`
* :arch-cpp:`virtualMemory.h`

.. _system_functions/classes:

Classes
~~~~~~~

* :arch-cpp:`arch::IntervalTimer`

.. _system_functions/macros:

Macros
~~~~~~

* :arch-cpp:`ARCH_GLOB_NOCHECK`
* :arch-cpp:`ARCH_GLOB_MARK`
* :arch-cpp:`ARCH_GLOB_NOSORT`
* :arch-cpp:`ARCH_GLOB_DEFAULT`
* :arch-cpp:`ARCH_PATH_MAX`
* :arch-cpp:`ARCH_PATH_SEP`
* :arch-cpp:`ARCH_PATH_LIST_SEP`
* :arch-cpp:`ARCH_REL_PATH_IDENT`

.. _system_functions/typedefs:

Typedefs
~~~~~~~~

* :arch-cpp:`arch::StatType`
* :arch-cpp:`arch::ConstFileMapping`
* :arch-cpp:`arch::MutableFileMapping`

.. _system_functions/enumerations:

Enumerations
~~~~~~~~~~~~

* :arch-cpp:`arch::MemAdvice`
* :arch-cpp:`arch::FileAdvice`

.. _system_functions/functions:

Functions
~~~~~~~~~

* :arch-cpp:`arch::HasEnv`
* :arch-cpp:`arch::GetEnv`
* :arch-cpp:`arch::SetEnv`
* :arch-cpp:`arch::RemoveEnv`
* :arch-cpp:`arch::ExpandEnvironmentVariables`
* :arch-cpp:`arch::StrError()`
* :arch-cpp:`arch::StrError(int)`
* :arch-cpp:`arch::OpenFile`
* :arch-cpp:`arch::GetFileLength(const char*)`
* :arch-cpp:`arch::GetFileLength(FILE*)`
* :arch-cpp:`arch::GetFileName`
* :arch-cpp:`arch::StatIsWritable`
* :arch-cpp:`arch::GetModificationTime(const char*, double*)`
* :arch-cpp:`arch::GetModificationTime(const StatType&)`
* :arch-cpp:`arch::NormPath`
* :arch-cpp:`arch::AbsPath`
* :arch-cpp:`arch::GetStatMode`
* :arch-cpp:`arch::GetTmpDir`
* :arch-cpp:`arch::MakeTmpFileName`
* :arch-cpp:`arch::MakeTmpFile(const std::string&, std::string* = nullptr)`
* :arch-cpp:`arch::MakeTmpFile(const std::string&, const std::string&, std::string* = nullptr)`
* :arch-cpp:`arch::MakeTmpSubdir`
* :arch-cpp:`arch::GetFileMappingLength(ConstFileMapping const &)`
* :arch-cpp:`arch::GetFileMappingLength(MutableFileMapping const &)`
* :arch-cpp:`arch::MapFileReadOnly(FILE*, std::string* = nullptr)`
* :arch-cpp:`arch::MapFileReadOnly(std::string const &, std::string* = nullptr)`
* :arch-cpp:`arch::MapFileReadWrite(FILE*, std::string* = nullptr)`
* :arch-cpp:`arch::MapFileReadWrite(std::string const &, std::string* = nullptr)`
* :arch-cpp:`arch::MemAdvise`
* :arch-cpp:`arch::QueryMappedMemoryResidency`
* :arch-cpp:`arch::PRead`
* :arch-cpp:`arch::PWrite`
* :arch-cpp:`arch::ReadLink`
* :arch-cpp:`arch::FileAdvise`
* :arch-cpp:`arch::LibraryOpen`
* :arch-cpp:`arch::LibraryClose`
* :arch-cpp:`arch::LibraryGetSymbolAddress`
* :arch-cpp:`arch::GetCwd`
* :arch-cpp:`arch::GetExecutablePath`
* :arch-cpp:`arch::GetPageSize`
* :arch-cpp:`arch::GetTickTime`
* :arch-cpp:`arch::GetStartTickTime`
* :arch-cpp:`arch::GetStopTickTime`
* :arch-cpp:`arch::GetTickQuantum`
* :arch-cpp:`arch::GetIntervalTimerTickOverhead`
* :arch-cpp:`arch::TicksToNanoseconds`
* :arch-cpp:`arch::TicksToSeconds`
* :arch-cpp:`arch::SecondsToTicks`
* :arch-cpp:`arch::MeasureExecutionTime`
