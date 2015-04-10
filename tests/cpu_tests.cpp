#include "gtest/gtest.h"
#include "../65zerodue.h"

using ::testing::Test;

TEST(cpu, load_accumulator_registry) {
    cpu6502 cpu;
    // LDA #$01
    cpu.execute(0xA901);
    EXPECT_EQ(cpu.accumulator, 1);
}
