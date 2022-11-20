#include <arch/timing.h>
#include <gtest/gtest.h>

#include <chrono>
#include <thread>


TEST(TimingTest, Conversion)
{
    // Verify conversions for many tick counts.
    for (size_t ticks = 0ul; ticks != 1ul << 24u; ++ticks) {
        ASSERT_EQ(
            (uint64_t)arch::TicksToNanoseconds(ticks),
            uint64_t(
                static_cast<double>(ticks) * arch::GetNanosecondsPerTick()
                + .5));

        double nanos = double(arch::TicksToNanoseconds(ticks)) / 1e9;
        double secs = arch::TicksToSeconds(ticks);
        double epsilon = 0.0001;
        ASSERT_TRUE((nanos - epsilon <= secs) && (nanos + epsilon >= secs));
    }
}

TEST(TimingTest, Delta)
{
    // Compute some time delta.
    const auto t1 = arch::GetTickTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    const auto t2 = arch::GetTickTime();
    const auto delta = t2 - t1;

    // Verify the delta is reasonable.  We allow a lot of leeway on the top
    // end in case of heavy machine load.
    ASSERT_TRUE(arch::TicksToSeconds(delta) > 1.4);
    ASSERT_TRUE(arch::TicksToSeconds(delta) < 5.0);
}
