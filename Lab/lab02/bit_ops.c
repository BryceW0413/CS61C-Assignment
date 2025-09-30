#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns 
    // 0 or 1)
    unsigned mask = 0x0001 << n;
    return (x & mask) >> n;
}

// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    if(v == 0x0001){
        *x = *x | (0x0001 << n);
    }else{
        *x = *x & ~(0x0001 << n);
    }
}

// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    unsigned current = get_bit(*x, n);
    unsigned next = (current == 0x0000)? 0x0001: 0x0000;
    
    set_bit(x, n, next);
}

