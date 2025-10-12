/*

Assignment name  : reverse_bits
Expected files   : reverse_bits.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that takes a byte, reverses it, bit by bit (like the
example) and returns the result.

Your function must be declared as follows:

unsigned char	reverse_bits(unsigned char octet);

Example:

  1 byte
_____________
 0100  0001
     ||
     \/
 1000  0010

*/

#include <stdio.h>

unsigned char reverse_bits(unsigned char octet)
{
    unsigned char res = 0;
    int i = 8;
    
    while (i > 0)
    {
        res = (res << 1) | (octet & 1);  // Shift left, then add rightmost bit
        octet = octet >> 1;               // Shift octet right to get next bit
        i--;
    }
    return res;
}

int main() {
	printf("%d\n", reverse_bits(2));
	printf("%d\n", reverse_bits_2(2));
}

/*
===============================================================================
DETAILED EXPLANATION OF BIT MANIPULATION
===============================================================================

HOW BITWISE AND (&) WORKS:
- The & operator compares each bit position and returns 1 only if BOTH bits are 1
- Truth table: 0&0=0, 0&1=0, 1&0=0, 1&1=1

EXAMPLE: octet & 1 extracts the rightmost bit
octet = 65 (01000001)
octet & 1 = 01000001 & 00000001 = 00000001 = 1

Why this works:
- All left 7 bits: 0&0=0 (become 0)
- Rightmost bit: 1&1=1 (survives!)
- Result: 0 or 1 depending on if rightmost bit was set

HOW BITWISE OR (|) WORKS:
- The | operator returns 1 if EITHER bit is 1
- Truth table: 0|0=0, 0|1=1, 1|0=1, 1|1=1

EXAMPLE: 00000000 | 00000001 = 00000001
Position 7: 0|0=0, Position 6: 0|0=0, ..., Position 0: 0|1=1
Result: Only the rightmost position becomes 1

HOW BIT SHIFTING WORKS:
- << (left shift): moves all bits left, fills right with 0
- >> (right shift): moves all bits right, fills left with 0

EXAMPLE: 00000001 << 1 = 00000010
EXAMPLE: 01000001 >> 1 = 00100000

===============================================================================
STEP-BY-STEP BREAKDOWN OF CORRECT BIT-SHIFTING ALGORITHM
===============================================================================

Let's reverse 01000001 (65) to get 10000010 (130):

INITIAL: res = 00000000, octet = 01000001

STEP 1 (i=8):
1a) Extract rightmost bit: octet & 1 = 01000001 & 00000001 = 00000001 = 1
1b) Shift res left: res << 1 = 00000000 << 1 = 00000000
1c) Combine with OR: res = 00000000 | 00000001 = 00000001
1d) Shift octet right: octet >> 1 = 01000001 >> 1 = 00100000
RESULT: res = 00000001, octet = 00100000

STEP 2 (i=7):
2a) Extract rightmost bit: octet & 1 = 00100000 & 00000001 = 00000000 = 0
2b) Shift res left: res << 1 = 00000001 << 1 = 00000010
2c) Combine with OR: res = 00000010 | 00000000 = 00000010
2d) Shift octet right: octet >> 1 = 00100000 >> 1 = 00010000
RESULT: res = 00000010, octet = 00010000

STEP 3 (i=6):
3a) Extract rightmost bit: octet & 1 = 00010000 & 00000001 = 00000000 = 0
3b) Shift res left: res << 1 = 00000010 << 1 = 00000100
3c) Combine with OR: res = 00000100 | 00000000 = 00000100
3d) Shift octet right: octet >> 1 = 00010000 >> 1 = 00001000
RESULT: res = 00000100, octet = 00001000

... continues for all 8 bits ...

FINAL RESULT: res = 10000010 (130 in decimal)

===============================================================================
WHY THE ORIGINAL CODE DOESN'T WORK
===============================================================================

The original implementation:
res |= (octet >> i);
res <<= 1;

This approach doesn't work because:
1) (octet >> i) shifts the entire octet by i positions
2) This doesn't extract individual bits one by one
3) The OR operation doesn't build the result correctly
4) The left shift happens after the OR, which is wrong order

===============================================================================
ARITHMETIC APPROACH EXPLANATION
===============================================================================

The arithmetic approach works by:
1) Using modulo 2 (octet % 2) to get the rightmost bit
2) Multiplying result by 2 (equivalent to left shift)
3) Adding the extracted bit
4) Dividing octet by 2 (equivalent to right shift)

This is mathematically equivalent to the bit-shifting approach
but uses arithmetic operations instead of bitwise operations.

===============================================================================
*/


/*

while (i > 0)
res = (res << 1) | (octet & 1);
octet = octet >> 1;
i--;

/*