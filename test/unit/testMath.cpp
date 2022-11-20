#include <arch/math.h>
#include <gtest/gtest.h>

#include <string>

static testing::AssertionResult IsCompliant(bool cond, const char* type)
{
    if (!cond) {
        return testing::AssertionFailure()
               << "failed: " << type << " is not IEEE-754 compliant";
    }

    return testing::AssertionSuccess() << type << " is IEEE-754 compliant.";
}

TEST(MathTest, FloatIEEE754Compliance)
{
    auto a = 5.6904566e-28f;
    auto b = 0x12345678;
    auto cond =
        (arch::FloatToBitPattern(a) == b && arch::BitPatternToFloat(b) == a);

    ASSERT_TRUE(IsCompliant(cond, "float"));
}

TEST(MathTest, DoubleIEEE754Compliance)
{
    auto a = 5.6263470058989390e-221;
    auto b = 0x1234567811223344ULL;
    auto cond =
        (arch::DoubleToBitPattern(a) == b && arch::BitPatternToDouble(b) == a);

    ASSERT_TRUE(IsCompliant(cond, "double"));
}

TEST(MathTest, Sign)
{
    ASSERT_EQ(arch::Sign(-123), -1);
    ASSERT_EQ(arch::Sign(123), 1);
    ASSERT_EQ(arch::Sign(0), 0);
}

TEST(MathTest, CountTrailingZeros)
{
    ASSERT_EQ(arch::CountTrailingZeros(1), 0);
    ASSERT_EQ(arch::CountTrailingZeros(2), 1);
    ASSERT_EQ(arch::CountTrailingZeros(3), 0);
    ASSERT_EQ(arch::CountTrailingZeros(4), 2);
    ASSERT_EQ(arch::CountTrailingZeros(5), 0);
    ASSERT_EQ(arch::CountTrailingZeros(6), 1);
    ASSERT_EQ(arch::CountTrailingZeros(7), 0);
    ASSERT_EQ(arch::CountTrailingZeros(8), 3);

    ASSERT_EQ(arch::CountTrailingZeros(65535), 0);
    ASSERT_EQ(arch::CountTrailingZeros(65536), 16);

    ASSERT_EQ(arch::CountTrailingZeros(~((1ull << 32ull) - 1ull)), 32);
    ASSERT_EQ(arch::CountTrailingZeros(1ull << 63ull), 63);
}
