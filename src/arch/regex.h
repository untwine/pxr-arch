// Copyright 2022 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
// Modified by Jeremy Retailleau

#ifndef ARCH_REGEX_H
#define ARCH_REGEX_H

#include <memory>
#include <string>

#include "arch/api.h"

namespace arch {

class Regex {
  public:
    static constexpr unsigned int CASE_INSENSITIVE = 1u;
    static constexpr unsigned int GLOB = 2u;

    /// Create an empty regex.
    ARCH_API Regex() = default;
    ARCH_API explicit Regex(const std::string& pattern, unsigned int flags = 0);
    Regex(const Regex&) = delete;
    ARCH_API Regex(Regex&&) noexcept;
    Regex& operator=(const Regex&) = delete;
    ARCH_API Regex& operator=(Regex&&) noexcept;
    ARCH_API ~Regex() = default;

    /// Returns \c true if the regex is valid.
    ARCH_API explicit operator bool() const;

    /// Returns the reason the regex is invalid or the empty string if
    /// it's valid.
    ARCH_API std::string GetError() const;

    /// Returns the flags used to construct the regex.
    ARCH_API unsigned int GetFlags() const;

    /// Returns \c true if the regex matches \p query anywhere, otherwise
    /// returns \c false.
    ARCH_API bool Match(const std::string& query) const;

  private:
    class _Impl;
    unsigned int _flags = 0;
    std::string _error;
    std::unique_ptr<_Impl> _impl;
};

}  // namespace arch

#endif  // ARCH_REGEX_H
