#include "gtest/gtest.h"
#include "../cpu6502.h"

using ::testing::Test;

TEST(cpu, load_accumulator_registry_value1) {
    uint8_t memory[] = {0xA9, 0x01};    // LDA #$01
    cpu6502 cpu(memory);
    cpu.step();
    EXPECT_EQ(cpu.accumulator, 1);
}

TEST(cpu, load_accumulator_registry_value2) {
    uint8_t memory[] = {0xA9, 0x02};    // LDA #$02
    cpu6502 cpu(memory);
    cpu.step();
    EXPECT_EQ(cpu.accumulator, 2);
}

TEST(cpu, multiple_steps_instructions_LDA_and_STA) {
    uint8_t memory[2000] = {0xa9, 0x01,         // LDA #$01
                            0x8d, 0x00, 0x02,   // STA $0200
                            0xa9, 0x05,         // LDA #$05
                            0x8d, 0x01, 0x02,   // STA $0201
                            0xa9, 0x08,         // LDA #$08
                            0x8d, 0x02, 0x02};  // STA $0202
    cpu6502 cpu(memory);
    cpu.step(6);
    EXPECT_EQ(cpu.accumulator, 8);
    EXPECT_EQ(memory[0x200], 0x01);
    EXPECT_EQ(memory[0x201], 0x05);
    EXPECT_EQ(memory[0x202], 0x08);
    EXPECT_EQ(cpu.pc, 0xF);
}
    
TEST(cpu, multiple_steps_instructions_LDA_TAX_INX_ADC_BRK) {
    uint8_t memory[2000] = {0xa9, 0xc0, // LDA #$c0  ;Load the hex value $c0 into the A register
                            0xaa,       // TAX       ;Transfer the value in the A register to X
                            0xe8,       // INX       ;Increment the value in the X register
                            0x69, 0xc4, // ADC #$c4  ;Add the hex value $c4 to the A register
                            0x00};      // BRK       ;Break - we're done
    cpu6502 cpu(memory);
    cpu.step(5);
    EXPECT_EQ(cpu.x, 0xc1);
    EXPECT_EQ(cpu.accumulator, 0x84);
    EXPECT_EQ(cpu.pc, 0x7);
    EXPECT_EQ(cpu.status.carry, 1);
}