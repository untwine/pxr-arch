// Copyright 2016 Pixar
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
// Modified by Jeremy Retailleau.

#include <pxr/arch/demangle.h>
#include <pxr/arch/error.h>

namespace pxr {

class DummyClassInNamespace {};
class OtherDummyClassInNamespace {
    public: class SubClass { };
};

template <class T>
class TemplatedDummyClassInNamespace { };

}  // namespace pxr


using namespace pxr;

template <class T>
class TemplatedDummyClass { };

struct Mangled {};

struct FooSsSsSsBar {};

template <class T>
class MangledAlso {};

typedef Mangled Remangled;

enum MangleEnum { ONE, TWO, THREE };

template <typename T>
static bool
TestDemangle(const std::string& typeName)
{
    const std::type_info& typeInfo = typeid(T);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ARCH_AXIOM(ArchDemangle(&toBeDemangledName));

    printf("ArchDemangle('%s') => '%s', expected '%s'\n",
        mangledName.c_str(), toBeDemangledName.c_str(), typeName.c_str());

    ARCH_AXIOM(toBeDemangledName == typeName);
    ARCH_AXIOM(ArchGetDemangled(mangledName) == typeName);
    ARCH_AXIOM(ArchGetDemangled(typeInfo) == typeName);
    ARCH_AXIOM(ArchGetDemangled<T>() == typeName);

    return true;
}

int main()
{
    TestDemangle<bool>("bool");
    TestDemangle<Mangled>("Mangled");
    TestDemangle<Remangled>("Mangled");
    TestDemangle<MangleEnum>("MangleEnum");
    // We have special case code for std::string.
    TestDemangle<std::string>("string");
    TestDemangle<TemplatedDummyClass<std::string>>(
        "TemplatedDummyClass<string>");
    // This one is a regression test for a demangle bug on Linux.
    TestDemangle<FooSsSsSsBar>("FooSsSsSsBar");

    TestDemangle<DummyClassInNamespace>("pxr::DummyClassInNamespace");
    TestDemangle<OtherDummyClassInNamespace::SubClass>("pxr::OtherDummyClassInNamespace::SubClass");
    TestDemangle<TemplatedDummyClassInNamespace<DummyClassInNamespace>>(
        "pxr::TemplatedDummyClassInNamespace<pxr::DummyClassInNamespace>");
    TestDemangle<TemplatedDummyClassInNamespace<OtherDummyClassInNamespace::SubClass>>(
        "pxr::TemplatedDummyClassInNamespace<pxr::OtherDummyClassInNamespace::SubClass>");

    TestDemangle<unsigned long>("unsigned long");
    TestDemangle<MangledAlso<int> >("MangledAlso<int>");
    TestDemangle<MangledAlso<MangledAlso<int> > >("MangledAlso<MangledAlso<int> >");

    const char* const badType = "type_that_doesnt_exist";
#if defined(ARCH_OS_WINDOWS)
    ARCH_AXIOM(ArchGetDemangled(badType) == badType);
#else
    ARCH_AXIOM(ArchGetDemangled(badType) == "");
#endif
   
    return 0;
}
