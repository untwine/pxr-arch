#include <arch/vsnprintf.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <string>


static int Snprintf(char* str, size_t size, const char* fmt, ...)
{
    int n;
    va_list ap;
    va_start(ap, fmt);

    n = arch::Vsnprintf(str, size, fmt, ap);

    va_end(ap);
    return n;
}

TEST(VsnprintfTest, Print)
{
    char str[1] = "";

    // Snprintf should report 3 characters not written
    ASSERT_EQ(Snprintf(str, strlen(str), "   "), 3);

    // ensure that a string longer than 4096 works
    // create a long format string
    char long_fmt[8192];
    for (int i = 0; i < 8191; ++i) {
        long_fmt[i] = ' ';
    }
    long_fmt[8191] = '\0';

    ASSERT_EQ(arch::StringPrintf("%s", long_fmt).size(), 8191);
}
