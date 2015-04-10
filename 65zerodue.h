#include <stdint.h>

class cpu6502 {
public:
    cpu6502();
    virtual ~cpu6502();
    int execute(uint32_t opcode) {
        accumulator = 1;
    }
    uint16_t accumulator;
};
