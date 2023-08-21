.. _diagnostics:

***********
Diagnostics
***********

Functions having to do with error reporting/handling.

.. _diagnostics/files:

Files
~~~~~

* :arch-cpp:`error.h`
* :arch-cpp:`stackTrace.h`
* :arch-cpp:`symbols.h`

.. _diagnostics/macros:

Macros
~~~~~~

* :arch-cpp:`ARCH_ERROR`
* :arch-cpp:`ARCH_WARNING`
* :arch-cpp:`ARCH_AXIOM`

.. _diagnostics/typedefs:

Typedefs
~~~~~~~~

* :arch-cpp:`arch::StackTraceCallback`
* :arch-cpp:`arch::CrashHandlerSystemCB`

.. _diagnostics/functions:

Functions
~~~~~~~~~

* :arch-cpp:`arch::LogFatalProcessState`
* :arch-cpp:`arch::LogCurrentProcessState`
* :arch-cpp:`arch::SetProcessStateLogCommand`
* :arch-cpp:`arch::IsAppCrashing`
* :arch-cpp:`arch::LogSessionInfo`
* :arch-cpp:`arch::SetLogSession`
* :arch-cpp:`arch::EnableSessionLogging`
* :arch-cpp:`arch::PrintStackTrace(FILE*, const std::string&, const std::string&)`
* :arch-cpp:`arch::PrintStackTrace(FILE*, const std::string&)`
* :arch-cpp:`arch::PrintStackTrace(std::ostream&, const std::string&, const std::string&)`
* :arch-cpp:`arch::PrintStackTrace(std::ostream&, const std::string&)`
* :arch-cpp:`arch::SetStackTraceCallback`
* :arch-cpp:`arch::GetStackTraceCallback`
* :arch-cpp:`arch::GetAppLaunchTime`
* :arch-cpp:`arch::SetFatalStackLogging`
* :arch-cpp:`arch::GetFatalStackLogging`
* :arch-cpp:`arch::SetProgramNameForErrors`
* :arch-cpp:`arch::GetProgramNameForErrors`
* :arch-cpp:`arch::SetProgramInfoForErrors`
* :arch-cpp:`arch::GetProgramInfoForErrors`
* :arch-cpp:`arch::SetExtraLogInfoForErrors`
* :arch-cpp:`arch::LogStackTrace(const std::string&, const std::string&, bool = false, const std::string& = "")`
* :arch-cpp:`arch::LogStackTrace(const std::string&, bool = false, const std::string& = "")`
* :arch-cpp:`arch::GetStackTrace`
* :arch-cpp:`arch::GetStackFrames(size_t, std::vector< uintptr_t >*)`
* :arch-cpp:`arch::GetStackFrames(size_t, uintptr_t*)`
* :arch-cpp:`arch::GetStackFrames(size_t, size_t, std::vector< uintptr_t >*)`
* :arch-cpp:`arch::GetStackFrames(size_t, size_t, uintptr_t*)`
* :arch-cpp:`arch::PrintStackFrames`
* :arch-cpp:`arch::CrashHandlerSystemv`
* :arch-cpp:`arch::GetAddressInfo`
