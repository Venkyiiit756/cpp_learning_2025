/*
 * Bitwise AND Operator (&) in C and C++
 * --------------------------------------
 * The bitwise AND operator compares each bit of two numbers and returns a new number where each bit is 1 only if both corresponding bits of the operands are 1.
 *
 * Example:
 *   0b1100 (12)
 * & 0b1010 (10)
 * = 0b1000 (8)
 *
 * Use Cases:
 * 1. Masking bits: Extract specific bits from a value.
 * 2. Checking if a bit is set: Test if a particular bit is 1.
 * 3. Clearing specific bits: Set certain bits to 0 while leaving others unchanged.
 * 4. Working with flags: Store and check multiple boolean flags in a single variable.
 * 5. Permissions: Check for specific access rights in systems programming.
 * 6. Data Compression and Packing: Extracting Color Channels
 * 7. Simple CRC-like Checksum Example
 * 8. Efficient Modulo for Powers of Two (Circular Buffer)
 * 9. Character Case Conversion (ASCII)
 * 10. Image Processing (Extracting Alpha Channel)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

int main() {
    // 1. Data Compression and Packing (Extracting Color Channels)
    // ----------------------------------------------------------
    // Many applications store multiple values (like colors) in a single integer for efficiency.
    // Bitwise AND is used to extract individual components (channels) from the packed value.
    uint32_t color = 0xAABBCCDD; // ARGB: AA (alpha), BB (red), CC (green), DD (blue)
    uint8_t blue = color & 0xFF;         // Mask out all but the lowest 8 bits (blue)
    uint8_t green = (color >> 8) & 0xFF; // Shift right 8 bits, then mask (green)
    uint8_t red = (color >> 16) & 0xFF;  // Shift right 16 bits, then mask (red)
    uint8_t alpha = (color >> 24) & 0xFF;// Shift right 24 bits, then mask (alpha)
    printf("\n[1] Data Compression and Packing (Extracting Color Channels)\n");
    printf("Color: 0x%X\nAlpha: 0x%X, Red: 0x%X, Green: 0x%X, Blue: 0x%X\n\n", color, alpha, red, green, blue);

    // 2. Simple CRC-like Checksum Example
    // -----------------------------------
    // Checksums often use bitwise AND to mask out certain bits.
    uint8_t data = 0b11010110;
    uint8_t crc_mask = 0x0F; // Only lower 4 bits matter
    uint8_t checksum = data & crc_mask; // Mask out upper bits
    printf("[2] Simple CRC-like Checksum Example\n");
    printf("Data: 0x%X, CRC Mask: 0x%X, Checksum: 0x%X\n\n", data, crc_mask, checksum);

    // 3. Efficient Modulo for Powers of Two (Circular Buffer)
    // ------------------------------------------------------
    // Bitwise AND can be used for fast modulo when the divisor is a power of two.
    int buffer[8];
    int index = 13;
    int wrapped = index & 7; // 13 % 8 == 5; 7 is 0b111
    printf("[3] Efficient Modulo for Powers of Two (Circular Buffer)\n");
    printf("Index: %d, Wrapped Index (index %% 8): %d\n\n", index, wrapped);

    // 4. Character Case Conversion (ASCII)
    // ------------------------------------
    // In ASCII, setting or clearing certain bits changes case.
    // AND with 0xDF (1101 1111) clears bit 5, converting lowercase to uppercase.
    char lower = 'g';
    char upper = lower & 0xDF; // Convert to uppercase
    printf("[4] Character Case Conversion (ASCII)\n");
    printf("Original: %c, Uppercase: %c\n\n", lower, upper);

    // 5. Image Processing (Extracting Alpha Channel)
    // ----------------------------------------------
    // Many image formats pack ARGB values into a single integer.
    // Bitwise AND is used to extract the alpha channel.
    uint32_t pixel = 0x80FF00FF; // ARGB: 0x80 (alpha), 0xFF (red), 0x00 (green), 0xFF (blue)
    uint8_t alpha_channel = (pixel >> 24) & 0xFF;
    printf("[5] Image Processing (Extracting Alpha Channel)\n");
    printf("Pixel: 0x%X, Alpha Channel: 0x%X\n\n", pixel, alpha_channel);

    // 6. Protocol Decoding (Parsing a Packed Byte)
    // --------------------------------------------
    // Communication protocols often pack multiple fields into a byte.
    // Bitwise AND and shifts extract each field.
    uint8_t packet = 0b10110110; // [7:6]=type, [5:3]=address, [2:0]=data
    uint8_t type = (packet >> 6) & 0x03;     // Extract bits 7-6 (type)
    uint8_t address = (packet >> 3) & 0x07;  // Extract bits 5-3 (address)
    uint8_t data_field = packet & 0x07;      // Extract bits 2-0 (data)
    printf("[6] Protocol Decoding (Parsing a Packed Byte)\n");
    printf("Packet: 0x%X, Type: %u, Address: %u, Data: %u\n\n", packet, type, address, data_field);

    // 7. Game Development (Object State Flags)
    // ----------------------------------------
    // Each bit in a variable can represent a different state (alive, visible, invincible, etc).
    // Bitwise operations allow you to efficiently store and check multiple states.
    #define STATE_ALIVE      0x01 // 0000 0001
    #define STATE_VISIBLE    0x02 // 0000 0010
    #define STATE_INVINCIBLE 0x04 // 0000 0100
    uint8_t player_state = STATE_ALIVE | STATE_VISIBLE; // Player is alive and visible
    printf("[7] Game Development (Object State Flags)\n");
    printf("Player State: 0x%X\n", player_state);
    if (player_state & STATE_ALIVE) printf("Player is alive.\n");
    if (player_state & STATE_VISIBLE) printf("Player is visible.\n");
    if (!(player_state & STATE_INVINCIBLE)) printf("Player is not invincible.\n");
    printf("\n");

    // 8. Math Tricks (Even/Odd, Power of Two Check)
    // ---------------------------------------------
    // Bitwise AND is a fast way to check if a number is even or odd, or if it's a power of two.
    int num = 42;
    printf("[8] Math Tricks (Even/Odd, Power of Two Check)\n");
    printf("%d is %s\n", num, (num & 1) ? "odd" : "even");
    int n = 64;
    printf("%d is %sa power of two\n\n", n, (n && !(n & (n-1))) ? "" : "not ");

    // 9. Feature Toggles (Feature Mask)
    // ---------------------------------
    // Each bit in a mask can represent the ON/OFF state of a feature.
    #define FEATURE_A 0x01 // 0000 0001
    #define FEATURE_B 0x02 // 0000 0010
    #define FEATURE_C 0x04 // 0000 0100
    uint8_t feature_mask = FEATURE_A | FEATURE_C; // Enable features A and C
    printf("[9] Feature Toggles (Feature Mask)\n");
    printf("Feature Mask: 0x%X\n", feature_mask);
    printf("Feature A: %s\n", (feature_mask & FEATURE_A) ? "enabled" : "disabled");
    printf("Feature B: %s\n", (feature_mask & FEATURE_B) ? "enabled" : "disabled");
    printf("Feature C: %s\n", (feature_mask & FEATURE_C) ? "enabled" : "disabled");
    printf("\n");

    // 10. Masking bits: Extract specific bits from a value
    // ----------------------------------------------------
    // Bitwise AND with a mask extracts only the bits you want.
    int value = 0xABCD;
    int lower_byte = value & 0x00FF; // Mask out all but the lowest 8 bits
    printf("[10] Masking bits: Extract specific bits from a value\n");
    printf("Original value: 0x%X\n", value);
    printf("Lower byte (masked): 0x%X\n\n", lower_byte);

    // 11. Checking if a bit is set: Test if bit 3 is set
    // --------------------------------------------------
    // Bitwise AND with a mask for the bit checks if that bit is set.
    printf("[11] Checking if a bit is set\n");
    if (value & (1 << 3)) {
        printf("Bit 3 is set in 0x%X.\n\n", value);
    } else {
        printf("Bit 3 is not set in 0x%X.\n\n", value);
    }

    // 12. Clearing specific bits: Clear bit 2
    // ----------------------------------------
    // Bitwise AND with the complement of a bit mask clears that bit.
    int cleared = value & ~(1 << 2);
    printf("[12] Clearing specific bits: Clear bit 2\n");
    printf("Value after clearing bit 2: 0x%X\n\n", cleared);

    // 13. Working with flags: Store and check multiple boolean flags
    // ------------------------------------------------------------
    // In many applications, you may want to keep track of several ON/OFF (true/false) states efficiently.
    // Instead of using separate variables for each state, you can use one integer and assign each bit to a different flag.
    // Here, FLAG_A, FLAG_B, and FLAG_C each represent a single bit in the integer 'flags'.
    //
    // FLAG_A = 0x01 = 0000 0001 (bit 0)
    // FLAG_B = 0x02 = 0000 0010 (bit 1)
    // FLAG_C = 0x04 = 0000 0100 (bit 2)
    //
    // Setting flags: Use bitwise OR (|) to turn ON specific flags.
    // For example, FLAG_A | FLAG_C = 0000 0101, so bits 0 and 2 are set.
    #define FLAG_A 0x01
    #define FLAG_B 0x02
    #define FLAG_C 0x04
    int flags = FLAG_A | FLAG_C; // Set FLAG_A and FLAG_C (bits 0 and 2)
    printf("[13] Working with flags: Store and check multiple boolean flags\n");
    printf("Flags value: 0x%X\n", flags);
    // Checking if a flag is set: Use bitwise AND (&) to test if a specific flag is ON.
    // If the result is not zero, the flag is set.
    if (flags & FLAG_B) {
        printf("FLAG_B is set.\n");
    } else {
        printf("FLAG_B is not set.\n");
    }
    if (flags & FLAG_C) {
        printf("FLAG_C is set.\n");
    }
    printf("\n");

    // 14. Permissions: Check for specific access rights
    // ------------------------------------------------
    // This is a common pattern in operating systems and security: each bit in an integer represents a permission.
    // For example, READ, WRITE, and EXEC permissions for a file or resource.
    //
    // READ  = 0x4 = 0000 0100 (bit 2)
    // WRITE = 0x2 = 0000 0010 (bit 1)
    // EXEC  = 0x1 = 0000 0001 (bit 0)
    //
    // To grant permissions, use bitwise OR (|). Here, we grant READ and WRITE.
    #define READ  0x4
    #define WRITE 0x2
    #define EXEC  0x1
    int permissions = READ | WRITE; // Has read and write (bits 2 and 1)
    printf("[14] Permissions: Check for specific access rights\n");
    printf("Permissions value: 0x%X\n", permissions);
    // To check for multiple permissions, use bitwise AND (&) and compare to zero.
    if ((permissions & READ) && (permissions & WRITE)) {
        printf("Has both read and write permissions.\n");
    }
    if (!(permissions & EXEC)) {
        printf("Does not have execute permission.\n");
    }

    return 0;
}
