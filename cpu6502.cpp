#include "cpu6502.h"
#include <cstdlib>
#include <iostream>

cpu6502::cpu6502(uint8_t *memory)
                :pc(0),cycles(0) {
    if (memory == NULL) {
        this->memory = (uint8_t*)malloc(MAX_MEMORY);
    } else {
        this->memory = memory;
    }
};

cpu6502::~cpu6502() {
    // TODO: deallocated memory allocated if you did it
}

int cpu6502::step(int nsteps) {
    for(int i=0; i<nsteps; i++) {
        if (memory[pc] == 0xA9) {
            accumulator = memory[pc+1];
            pc += 2;
            cycles += 2;
        }
        else if (memory[pc] == 0x8d) {
            uint16_t address = memory[pc+2];
            address = address << 8;
            address |= memory[pc+1];
            memory[address] = accumulator;
            pc += 3;
            cycles += 4;
        }
        else {
            std::cout << "The instruction is not valid" << std::endl;
        }
    }
}
