#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t b0 = (*reg & 0x00001);
    uint16_t b2 = (*reg & (0x00001) << 2) >> 2;
    uint16_t b3 = (*reg & (0x00001) << 3) >> 3;
    uint16_t b5 = (*reg & (0x00001) << 5) >> 5;

    uint16_t new_bit = b0^b2^b3^b5;

    *reg = (*reg >> 1) | (new_bit << 15);
}

