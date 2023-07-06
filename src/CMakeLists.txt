set(PLATFORM_LIBS "")

if (WIN32)
    set(PLATFORM_LIBS Ws2_32.lib Dbghelp.lib)
endif()

add_library(arch
    arch/assumptions.cpp
    arch/attributes.cpp
    arch/daemon.cpp
    arch/debugger.cpp
    arch/demangle.cpp
    arch/env.cpp
    arch/errno.cpp
    arch/error.cpp
    arch/fileSystem.cpp
    arch/function.cpp
    arch/hash.cpp
    arch/initConfig.cpp
    arch/library.cpp
    arch/mallocHook.cpp
    arch/regex.cpp
    arch/stackTrace.cpp
    arch/symbols.cpp
    arch/systemInfo.cpp
    arch/threads.cpp
    arch/timing.cpp
    arch/virtualMemory.cpp
    arch/vsnprintf.cpp
)

target_include_directories(arch
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(arch
    PUBLIC
        Threads::Threads
        ${CMAKE_DL_LIBS}
	${PLATFORM_LIBS}
)

if (ENABLE_PRECOMPILED_HEADERS)
    target_precompile_headers(arch 
        PRIVATE 
            arch/pch.h
    )
endif()

install(TARGETS arch EXPORT ${PROJECT_NAME})
install(
    DIRECTORY
        arch
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT ${PROJECT_NAME}
    FILE archTargets.cmake
    NAMESPACE arch::
    DESTINATION share/cmake/arch
)
