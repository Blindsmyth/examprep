/*

Assignment name  : print_bits
Expected files   : print_bits.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a function that takes a byte, and prints it in binary WITHOUT A NEWLINE
AT THE END.

Your function must be declared as follows:

void	print_bits(unsigned char octet);

Example, if you pass 2 to print_bits, it will print "00000010"

*/

#include <unistd.h>

void	print_bits(unsigned char octet) {
    // This is the INTUITIVE way to print bits from left to right
    // We use a mask that starts at the leftmost bit and moves right
    
    unsigned char mask = 128;  // 10000000 in binary (leftmost bit position)
    
    int i = 0;
    while (i < 8) {
        // Check if the current bit is set (1) or not (0)
        if (octet & mask) {
            // If the bit is 1, print '1'
            write(1, "1", 1);
        } else {
            // If the bit is 0, print '0'
            write(1, "0", 1);
        }
        
        // Move the mask right by 1 position for the next bit
        mask = mask >> 1;
        i++;
    }
}

/*
===============================================================================
INTUITIVE APPROACH EXPLANATION
===============================================================================

This approach is much easier to understand because it follows your natural
thinking: "I want to check the leftmost bit, then the second leftmost, etc."

HOW IT WORKS:

1) START WITH A MASK: 10000000 (128 in decimal)
   - This mask has a 1 in the leftmost position
   - All other positions are 0

2) FOR EACH BIT POSITION:
   - Use the mask to check if that bit is set
   - Print '1' if the bit is set, '0' if not
   - Move the mask right by 1 position

STEP-BY-STEP EXAMPLE with octet = 65 (01000001):

ITERATION 1 (i=0):
- mask = 10000000 (128)
- octet & mask = 01000001 & 10000000 = 00000000 = 0
- Since result is 0, print '0'
- mask = mask >> 1 = 10000000 >> 1 = 01000000 (64)

ITERATION 2 (i=1):
- mask = 01000000 (64)
- octet & mask = 01000001 & 01000000 = 01000000 = 64
- Since result is not 0, print '1'
- mask = mask >> 1 = 01000000 >> 1 = 00100000 (32)

ITERATION 3 (i=2):
- mask = 00100000 (32)
- octet & mask = 01000001 & 00100000 = 00000000 = 0
- Since result is 0, print '0'
- mask = mask >> 1 = 00100000 >> 1 = 00010000 (16)

ITERATION 4 (i=3):
- mask = 00010000 (16)
- octet & mask = 01000001 & 00010000 = 00000000 = 0
- Since result is 0, print '0'
- mask = mask >> 1 = 00010000 >> 1 = 00001000 (8)

ITERATION 5 (i=4):
- mask = 00001000 (8)
- octet & mask = 01000001 & 00001000 = 00000000 = 0
- Since result is 0, print '0'
- mask = mask >> 1 = 00001000 >> 1 = 00000100 (4)

ITERATION 6 (i=5):
- mask = 00000100 (4)
- octet & mask = 01000001 & 00000100 = 00000000 = 0
- Since result is 0, print '0'
- mask = mask >> 1 = 00000100 >> 1 = 00000010 (2)

ITERATION 7 (i=6):
- mask = 00000010 (2)
- octet & mask = 01000001 & 00000010 = 00000000 = 0
- Since result is 0, print '0'
- mask = mask >> 1 = 00000010 >> 1 = 00000001 (1)

ITERATION 8 (i=7):
- mask = 00000001 (1)
- octet & mask = 01000001 & 00000001 = 00000001 = 1
- Since result is not 0, print '1'
- mask = mask >> 1 = 00000001 >> 1 = 00000000 (0)

FINAL OUTPUT: 01000001

===============================================================================
WHY THIS IS MORE INTUITIVE
===============================================================================

1) IT FOLLOWS YOUR THINKING: "Check leftmost bit, then second leftmost, etc."
2) THE MASK MOVES RIGHT: Just like reading from left to right
3) NO CONFUSING SHIFTING: We're not moving the octet around
4) CLEAR LOGIC: If bit is set, print '1'; if not, print '0'
5) EASY TO DEBUG: You can see exactly which bit is being checked

===============================================================================
COMPARISON WITH THE CONFUSING APPROACH
===============================================================================

ORIGINAL (Confusing):
- "To see the leftmost bit, shift everything right by 7 positions"
- "To see the second bit, shift everything right by 6 positions"
- Counterintuitive: "move right to see left"

NEW (Intuitive):
- "Check the leftmost bit with mask 10000000"
- "Check the second bit with mask 01000000"
- Intuitive: "check each position from left to right"

===============================================================================
*/

