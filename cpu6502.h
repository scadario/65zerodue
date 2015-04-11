#include <stdint.h>

#define MAX_MEMORY 65536
#define NULL 0

class cpu6502 {
public:
    cpu6502(uint8_t *memory = NULL);
    virtual ~cpu6502();
    int step(int nsteps = 1);
    
    uint8_t *memory;

    uint8_t accumulator;
    uint16_t pc;
    uint8_t x;
    uint8_t status;
    int cycles;
};
