#include <arch/function.h>
#include <gtest/gtest.h>

TEST(FunctionTest, GetPrettierFunctionName)
{
    // Non-member
    ASSERT_EQ(arch::GetPrettierFunctionName("Bar", "int Bar(float)"), "Bar");

    // Template non-member function
    ASSERT_EQ(
        arch::GetPrettierFunctionName("Bar", "int Bar(C) [with C = int]"),
        "Bar");
    ASSERT_EQ(arch::GetPrettierFunctionName("Bar", "int Bar<C>(C)"), "Bar");

    // Non-template class non-template member function
    ASSERT_EQ(
        arch::GetPrettierFunctionName("Bar", "int Foo::Bar(float)"),
        "Foo::Bar");

    // Template class member function
    ASSERT_EQ(
        arch::GetPrettierFunctionName(
            "Bar", "int Foo<A>::Bar(float) [with A = int]"),
        "Foo<A>::Bar [with A = int]");

    // Multi-parameter template class
    ASSERT_EQ(
        arch::GetPrettierFunctionName(
            "Bar", "int Foo<A,B>::Bar(float) [with A = int, B = int]"),
        "Foo<A,B>::Bar [with A = int, B = int]");

    // Template function
    ASSERT_EQ(
        arch::GetPrettierFunctionName(
            "Bar", "A Foo<A, B>::Bar(C) [with C = double; B = float; A = int]"),
        "Foo<A, B>::Bar [with A = int, B = float]");

    // Linux-style nested templates
    ASSERT_EQ(
        arch::GetPrettierFunctionName(
            "foo",
            "int X<A>::Y<B>::foo(A, B, C) [with C = bool; B = float; A = int]"),
        "X<A>::Y<B>::foo [with A = int, B = float]");

    // Linux-style nested templates with templates for template arguments
    ASSERT_EQ(
        arch::GetPrettierFunctionName(
            "foo",
            "int X<A>::Y<B>::foo(A, B, C) [with C = bool; B = "
            "Z<char, double>::W<short int>; A = Z<char, double>]"),
        "X<A>::Y<B>::foo [with A = Z<char, double>, B = "
        "Z<char, double>::W<short int>]");

    // Windows-style nested templates
    ASSERT_EQ(
        arch::GetPrettierFunctionName(
            "foo", "int __cdecl X<int>::Y<float>::foo<bool>(int,float,bool)"),
        "X<int>::Y<float>::foo");

    // Windows-style nested templates with templates for template arguments
    ASSERT_EQ(
        arch::GetPrettierFunctionName(
            "foo",
            "int __cdecl X<Z<char,double> >::Y<Z<char,double>::W<short> >"
            "::foo<bool>(Z<char,double>,Z<char,double>::W<short>,bool)"),
        "X<Z<char,double> >::Y<Z<char,double>::W<short> >::foo");

    // Edge cases.
    ASSERT_EQ(
        arch::GetPrettierFunctionName("operator<", "bool operator<(X, Y)"),
        "operator<");
    ASSERT_EQ(
        arch::GetPrettierFunctionName(
            "operator<", "bool Z<W>::operator<(Y) const [with W = int]"),
        "Z<W>::operator< [with W = int]");
    ASSERT_EQ(
        arch::GetPrettierFunctionName("operator<<", "int operator<<(X, int)"),
        "operator<<");
}