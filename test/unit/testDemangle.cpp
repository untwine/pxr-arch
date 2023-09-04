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
#include <gtest/gtest.h>

#include <string>

using namespace pxr;

struct MangledStruct {
};
typedef MangledStruct MangledStructAlias;

enum MangledEnum { ONE, TWO, THREE };

template <class T>
class MangledTemplatedClass {
};

// Ad std::string is mangled as 'Ss' on Linux, check that the following
// struct is properly demangled.
struct FooSsSsSsBar {
};

namespace archTest {

class MangledClass1 {
};

class MangledClass2 {
  public:
    class SubClass {
    };
};

}  // namespace archTest

TEST(DemangleTest, Bool)
{
    const std::type_info& typeInfo = typeid(bool);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "bool");
    ASSERT_EQ(arch::GetDemangled(mangledName), "bool");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "bool");
    ASSERT_EQ(arch::GetDemangled<bool>(), "bool");
}

TEST(DemangleTest, Struct)
{
    const std::type_info& typeInfo = typeid(MangledStruct);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "MangledStruct");
    ASSERT_EQ(arch::GetDemangled(mangledName), "MangledStruct");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "MangledStruct");
    ASSERT_EQ(arch::GetDemangled<MangledStruct>(), "MangledStruct");
}

TEST(DemangleTest, StructAlias)
{
    const std::type_info& typeInfo = typeid(MangledStructAlias);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "MangledStruct");
    ASSERT_EQ(arch::GetDemangled(mangledName), "MangledStruct");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "MangledStruct");
    ASSERT_EQ(arch::GetDemangled<MangledStructAlias>(), "MangledStruct");
}

TEST(DemangleTest, Enum)
{
    const std::type_info& typeInfo = typeid(MangledEnum);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "MangledEnum");
    ASSERT_EQ(arch::GetDemangled(mangledName), "MangledEnum");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "MangledEnum");
    ASSERT_EQ(arch::GetDemangled<MangledEnum>(), "MangledEnum");
}

TEST(DemangleTest, String)
{
    const std::type_info& typeInfo = typeid(std::string);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "string");
    ASSERT_EQ(arch::GetDemangled(mangledName), "string");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "string");
    ASSERT_EQ(arch::GetDemangled<std::string>(), "string");
}

TEST(DemangleTest, TemplatedClassString)
{
    const std::type_info& typeInfo = typeid(MangledTemplatedClass<std::string>);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "MangledTemplatedClass<string>");
    ASSERT_EQ(arch::GetDemangled(mangledName), "MangledTemplatedClass<string>");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "MangledTemplatedClass<string>");
    ASSERT_EQ(
        arch::GetDemangled<MangledTemplatedClass<std::string>>(),
        "MangledTemplatedClass<string>");
}

TEST(DemangleTest, StringConfusingMatch)
{
    const std::type_info& typeInfo = typeid(FooSsSsSsBar);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "FooSsSsSsBar");
    ASSERT_EQ(arch::GetDemangled(mangledName), "FooSsSsSsBar");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "FooSsSsSsBar");
    ASSERT_EQ(arch::GetDemangled<FooSsSsSsBar>(), "FooSsSsSsBar");
}

TEST(DemangleTest, Class)
{
    const std::type_info& typeInfo = typeid(archTest::MangledClass1);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "archTest::MangledClass1");
    ASSERT_EQ(arch::GetDemangled(mangledName), "archTest::MangledClass1");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "archTest::MangledClass1");
    ASSERT_EQ(
        arch::GetDemangled<archTest::MangledClass1>(),
        "archTest::MangledClass1");
}

TEST(DemangleTest, SubClass)
{
    const std::type_info& typeInfo = typeid(archTest::MangledClass2::SubClass);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "archTest::MangledClass2::SubClass");
    ASSERT_EQ(
        arch::GetDemangled(mangledName), "archTest::MangledClass2::SubClass");
    ASSERT_EQ(
        arch::GetDemangled(typeInfo), "archTest::MangledClass2::SubClass");
    ASSERT_EQ(
        arch::GetDemangled<archTest::MangledClass2::SubClass>(),
        "archTest::MangledClass2::SubClass");
}

TEST(DemangleTest, Long)
{
    const std::type_info& typeInfo = typeid(unsigned long);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "unsigned long");
    ASSERT_EQ(arch::GetDemangled(mangledName), "unsigned long");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "unsigned long");
    ASSERT_EQ(arch::GetDemangled<unsigned long>(), "unsigned long");
}

TEST(DemangleTest, TemplatedClassInt)
{
    const std::type_info& typeInfo = typeid(MangledTemplatedClass<int>);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(toBeDemangledName, "MangledTemplatedClass<int>");
    ASSERT_EQ(arch::GetDemangled(mangledName), "MangledTemplatedClass<int>");
    ASSERT_EQ(arch::GetDemangled(typeInfo), "MangledTemplatedClass<int>");
    ASSERT_EQ(
        arch::GetDemangled<MangledTemplatedClass<int>>(),
        "MangledTemplatedClass<int>");
}

TEST(DemangleTest, TemplatedClassRecursiveInt)
{
    const std::type_info& typeInfo =
        typeid(MangledTemplatedClass<MangledTemplatedClass<int>>);
    std::string mangledName = typeInfo.name();
    std::string toBeDemangledName = typeInfo.name();

    ASSERT_TRUE(arch::Demangle(&toBeDemangledName));

    ASSERT_EQ(
        toBeDemangledName,
        "MangledTemplatedClass<MangledTemplatedClass<int> >");
    ASSERT_EQ(
        arch::GetDemangled(mangledName),
        "MangledTemplatedClass<MangledTemplatedClass<int> >");
    ASSERT_EQ(
        arch::GetDemangled(typeInfo),
        "MangledTemplatedClass<MangledTemplatedClass<int> >");
    ASSERT_EQ(
        arch::GetDemangled<MangledTemplatedClass<MangledTemplatedClass<int>>>(),
        "MangledTemplatedClass<MangledTemplatedClass<int> >");
}

TEST(DemangleTest, IncorrectType)
{
    const char* const badType = "type_that_doesnt_exist";
#if defined(ARCH_OS_WINDOWS)
    ASSERT_EQ(arch::GetDemangled(badType), badType);
#else
    ASSERT_EQ(arch::GetDemangled(badType), "");
#endif
}
