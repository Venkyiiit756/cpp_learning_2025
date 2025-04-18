/**
 * Understanding CRC-8 (Cyclic Redundancy Check, 8-bit)
 * 
 * This file provides a detailed explanation of how CRC-8 works,
 * why it's more effective than simpler checksums, and breaks down
 * the algorithm step by step with examples.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <bitset>
#include <cstdint>

// CRC-8 implementation using polynomial x^8 + x^2 + x + 1 (0x07)
uint8_t crc8_checksum(const std::vector<uint8_t>& data) {
    // Initialize CRC to 0
    uint8_t crc = 0x00;
    for (uint8_t byte : data) {
        crc ^= byte;
        for (int i = 0; i < 8; ++i) {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x07;
            else
                crc <<= 1;
        }
    }
    return crc;
}

// Helper function to print byte in binary and hex
void print_byte(uint8_t byte, const std::string& label) {
    std::cout << label << ": 0b" << std::bitset<8>(byte) 
              << " (0x" << std::hex << std::setw(2) << std::setfill('0') 
              << static_cast<int>(byte) << std::dec << ")" << std::endl;
}

// Function to demonstrate CRC-8 calculation step by step
void demonstrate_crc8(const std::vector<uint8_t>& data) {
    std::cout << "Step-by-step CRC-8 calculation for data: ";
    for (auto byte : data) {
        std::cout << "0x" << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl << std::endl;

    // Initialize CRC to 0
    uint8_t crc = 0x00;
    std::cout << "Initialize CRC = 0x00" << std::endl;
    
    // Process each byte
    for (size_t j = 0; j < data.size(); ++j) {
        uint8_t byte = data[j];
        std::cout << "\nProcessing byte " << j+1 << ": ";
        print_byte(byte, "Input byte");
        
        // XOR with current CRC value
        std::cout << "  XOR with current CRC" << std::endl;
        print_byte(crc, "  Current CRC");
        crc ^= byte;
        print_byte(crc, "  After XOR");
        
        // Process each bit
        std::cout << "  Processing each bit:" << std::endl;
        for (int i = 0; i < 8; ++i) {
            std::cout << "    Bit " << i+1 << ": ";
            print_byte(crc, "    Current CRC");
            
            // Check MSB (Most Significant Bit)
            // Check if MSB is set using bitwise AND with 0x80
            bool msb_set = (crc & 0x80);
            std::cout << "    MSB is " << (msb_set ? "1" : "0") 
                     << " (crc & 0x80 is " << (msb_set ? "true" : "false") << ") --> ";
            
            if (msb_set) {
                // If MSB is 1: Shift left and XOR with polynomial
                std::cout << "Shift left and XOR with polynomial 0x07" << std::endl;
                print_byte(crc << 1, "      After shift");
                print_byte(0x07, "      Polynomial");
                crc = (crc << 1) ^ 0x07;
                print_byte(crc, "      Result");
            } else {
                // If MSB is 0: Just shift left
                std::cout << "Just shift left" << std::endl;
                crc <<= 1;
                print_byte(crc, "      Result");
            }
        }
    }
    
    std::cout << "\nFinal CRC-8 checksum: ";
    print_byte(crc, "");
}

// Demonstration of simpler checksum methods for comparison
void simple_checksum_demo(const std::vector<uint8_t>& data) {
    // 1. Simple sum
    uint8_t sum = 0;
    for (uint8_t byte : data) {
        sum += byte;
    }
    
    // 2. XOR checksum
    uint8_t xor_sum = 0;
    for (uint8_t byte : data) {
        xor_sum ^= byte;
    }
    
    std::cout << "Simple checksum comparisons:" << std::endl;
    print_byte(sum, "Sum checksum");
    print_byte(xor_sum, "XOR checksum");
    print_byte(crc8_checksum(data), "CRC-8 checksum");
}

// Function to demonstrate error detection capabilities
void error_detection_demo() {
    std::vector<uint8_t> original = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    std::vector<uint8_t> error1 = {0x48, 0x65, 0x6D, 0x6C, 0x6F};   // "Hemlo" (1-bit error)
    std::vector<uint8_t> error2 = {0x48, 0x65, 0x6C, 0x6F, 0x6C};   // "Helol" (swapped bytes)
    std::vector<uint8_t> error3 = {0x48, 0x45, 0x6C, 0x6C, 0x6F};   // "HEllo" (multi-bit error)
    
    // Calculate checksums
    uint8_t sum_orig = 0, sum_err1 = 0, sum_err2 = 0, sum_err3 = 0;
    uint8_t xor_orig = 0, xor_err1 = 0, xor_err2 = 0, xor_err3 = 0;
    
    for (size_t i = 0; i < original.size(); i++) {
        sum_orig += original[i];
        xor_orig ^= original[i];
        
        sum_err1 += error1[i];
        xor_err1 ^= error1[i];
        
        sum_err2 += error2[i];
        xor_err2 ^= error2[i];
        
        sum_err3 += error3[i];
        xor_err3 ^= error3[i];
    }
    
    uint8_t crc_orig = crc8_checksum(original);
    uint8_t crc_err1 = crc8_checksum(error1);
    uint8_t crc_err2 = crc8_checksum(error2);
    uint8_t crc_err3 = crc8_checksum(error3);
    
    std::cout << "\n*** ERROR DETECTION COMPARISON ***" << std::endl;
    std::cout << "Original data: 'Hello'" << std::endl;
    std::cout << "Error 1 (1-bit): 'Hemlo'" << std::endl;
    std::cout << "Error 2 (swapped): 'Helol'" << std::endl;
    std::cout << "Error 3 (multi-bit): 'HEllo'" << std::endl << std::endl;
    
    std::cout << "Sum checksum:" << std::endl;
    std::cout << "Original: 0x" << std::hex << static_cast<int>(sum_orig) << std::endl;
    std::cout << "Error 1: 0x" << std::hex << static_cast<int>(sum_err1) 
              << (sum_orig == sum_err1 ? " (UNDETECTED!)" : " (detected)") << std::endl;
    std::cout << "Error 2: 0x" << std::hex << static_cast<int>(sum_err2) 
              << (sum_orig == sum_err2 ? " (UNDETECTED!)" : " (detected)") << std::endl;
    std::cout << "Error 3: 0x" << std::hex << static_cast<int>(sum_err3) 
              << (sum_orig == sum_err3 ? " (UNDETECTED!)" : " (detected)") << std::endl << std::endl;
              
    std::cout << "XOR checksum:" << std::endl;
    std::cout << "Original: 0x" << std::hex << static_cast<int>(xor_orig) << std::endl;
    std::cout << "Error 1: 0x" << std::hex << static_cast<int>(xor_err1) 
              << (xor_orig == xor_err1 ? " (UNDETECTED!)" : " (detected)") << std::endl;
    std::cout << "Error 2: 0x" << std::hex << static_cast<int>(xor_err2) 
              << (xor_orig == xor_err2 ? " (UNDETECTED!)" : " (detected)") << std::endl;
    std::cout << "Error 3: 0x" << std::hex << static_cast<int>(xor_err3) 
              << (xor_orig == xor_err3 ? " (UNDETECTED!)" : " (detected)") << std::endl << std::endl;
              
    std::cout << "CRC-8 checksum:" << std::endl;
    std::cout << "Original: 0x" << std::hex << static_cast<int>(crc_orig) << std::endl;
    std::cout << "Error 1: 0x" << std::hex << static_cast<int>(crc_err1) 
              << (crc_orig == crc_err1 ? " (UNDETECTED!)" : " (detected)") << std::endl;
    std::cout << "Error 2: 0x" << std::hex << static_cast<int>(crc_err2) 
              << (crc_orig == crc_err2 ? " (UNDETECTED!)" : " (detected)") << std::endl;
    std::cout << "Error 3: 0x" << std::hex << static_cast<int>(crc_err3) 
              << (crc_orig == crc_err3 ? " (UNDETECTED!)" : " (detected)") << std::endl << std::endl;
              
    std::cout << std::dec;
}

int main() {
    std::cout << "=============================================" << std::endl;
    std::cout << "   UNDERSTANDING CRC-8 CHECKSUM ALGORITHM    " << std::endl;
    std::cout << "=============================================" << std::endl << std::endl;

    // Explanation section
    std::cout << "WHAT IS CRC-8?" << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << "CRC-8 is an 8-bit Cyclic Redundancy Check algorithm used for error detection" << std::endl;
    std::cout << "in digital networks and storage devices. It is more robust than simple checksums" << std::endl;
    std::cout << "like sum or XOR, and can detect more types of errors." << std::endl << std::endl;

    std::cout << "The algorithm uses a polynomial for division (in our case x^8 + x^2 + x + 1," << std::endl;
    std::cout << "which is represented as 0x07 in binary). This polynomial creates a mathematical" << std::endl;
    std::cout << "relationship between all bits in the data that helps detect various error patterns." << std::endl << std::endl;

    std::cout << "WHY TWO CASES IN THE ALGORITHM?" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "The two cases in the inner loop of the algorithm represent two different scenarios" << std::endl;
    std::cout << "in the CRC polynomial division process:" << std::endl << std::endl;

    std::cout << "1. When MSB is 1 (crc & 0x80):" << std::endl;
    std::cout << "   This means we need to perform polynomial division. We shift left (multiply by x)" << std::endl;
    std::cout << "   and then XOR with the polynomial (0x07). This XOR operation is equivalent to" << std::endl;
    std::cout << "   modulo-2 division in polynomial arithmetic." << std::endl << std::endl;

    std::cout << "2. When MSB is 0:" << std::endl;
    std::cout << "   No division is needed, we just shift left (multiply by x). In modulo-2 division," << std::endl;
    std::cout << "   you only XOR (subtract) when the bit aligns with a '1' in the dividend." << std::endl << std::endl;

    std::cout << "These two cases implement modulo-2 polynomial division, which is the mathematical" << std::endl;
    std::cout << "foundation of CRC algorithms." << std::endl << std::endl;

    // Demonstrate with examples
    std::cout << "Example 1: Simple data [0x01, 0x02]" << std::endl;
    std::cout << "=====================================" << std::endl;
    demonstrate_crc8({0x01, 0x02});
    
    std::cout << "\n\nExample 2: ASCII data 'AB' [0x41, 0x42]" << std::endl;
    std::cout << "==========================================" << std::endl;
    demonstrate_crc8({0x41, 0x42});
    
    // Compare with simpler checksum methods
    std::cout << "\n\nCOMPARISON WITH SIMPLER CHECKSUMS" << std::endl;
    std::cout << "=================================" << std::endl;
    simple_checksum_demo({0x41, 0x42});
    
    // Demonstrate error detection
    std::cout << "\n\nERROR DETECTION CAPABILITIES" << std::endl;
    std::cout << "===========================" << std::endl;
    error_detection_demo();
    
    // Conclusion
    std::cout << "\nWHY CRC-8 IS BETTER THAN SIMPLE CHECKSUMS" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "1. Bit Sensitivity: CRC is highly sensitive to changes in any bit position" << std::endl;
    std::cout << "   because each bit affects the polynomial division process." << std::endl << std::endl;
    
    std::cout << "2. Error Detection Capabilities:" << std::endl;
    std::cout << "   - Detects all single-bit errors" << std::endl;
    std::cout << "   - Detects all double-bit errors for certain message lengths" << std::endl;
    std::cout << "   - Detects any odd number of bit errors" << std::endl;
    std::cout << "   - Detects burst errors of length <= 8 bits" << std::endl;
    std::cout << "   - Detects most longer burst errors with high probability" << std::endl << std::endl;
    
    std::cout << "3. Simple checksums fail in many common error scenarios:" << std::endl;
    std::cout << "   - Sum checksum: Fails if errors cancel out (e.g., +1 in one byte, -1 in another)" << std::endl;
    std::cout << "   - XOR checksum: Fails if the same bit positions are changed in an even number of bytes" << std::endl;
    std::cout << "   - Both fail to detect byte swaps, as the order doesn't matter to them" << std::endl << std::endl;
    
    std::cout << "4. Mathematical Foundation: CRC has a strong mathematical foundation (polynomial algebra)" << std::endl;
    std::cout << "   that makes its error detection properties theoretically provable." << std::endl << std::endl;

    return 0;
}

/*
 * DETAILED EXPLANATION OF THE CRC-8 ALGORITHM
 * ==========================================
 *
 * The CRC-8 calculation algorithm can be broken down as follows:
 *
 * 1. INITIALIZATION:
 *    We start with a CRC value of 0x00. This is the initial state of our checksum.
 *
 * 2. PROCESSING EACH BYTE:
 *    For each byte in the input data:
 *    a. First, we XOR the current CRC value with the byte being processed.
 *       - This introduces the new byte's data into our calculation.
 *       - XOR is used because it's reversible and captures bit-level differences.
 *
 * 3. BIT-BY-BIT PROCESSING:
 *    For each of the 8 bits in the current byte (from MSB to LSB):
 *    a. We check if the most significant bit (MSB) of the current CRC value is 1 or 0.
 *       - This is checked using bitwise AND with mask 0x80 (10000000 in binary).
 *       - The condition (crc & 0x80) evaluates to true if MSB is 1, false if MSB is 0.
 *
 *    b. CASE 1: If MSB is 1 (when crc & 0x80 evaluates to true):
 *       - We shift the CRC value left by 1 bit, which effectively:
 *         i. Multiplies the polynomial by x
 *         ii. Discards the MSB that would overflow the 8-bit register
 *       - Then we perform bitwise XOR with the generator polynomial 0x07 (x^8 + x^2 + x + 1)
 *       - This operation simulates polynomial division where we're performing
 *         modulo-2 division by the generator polynomial.
 *       - Note: When MSB is 1, division is required because it means the degree
 *         of our current polynomial equals the degree of the generator polynomial.
 *
 *    c. CASE 2: If MSB is 0 (crc & 0x80 is false):
 *       - We simply shift the CRC value left by 1 bit.
 *       - No XOR is needed because in polynomial division, you only
 *         perform subtraction (XOR in GF(2)) when the degrees match.
 *
 * 4. MATHEMATICAL BASIS:
 *    - The algorithm implements division in the Galois Field GF(2) - a mathematical
 *      field with only two elements, 0 and 1, where addition and subtraction are the same
 *      operation (XOR), and multiplication is done modulo-2.
 *    - The generator polynomial 0x07 (x^8 + x^2 + x + 1) has specific mathematical
 *      properties that ensure good error detection capabilities.
 *
 * 5. BIT SENSITIVITY:
 *    - Every bit in the input data potentially affects every bit in the final CRC value.
 *    - This is due to the polynomial division process that propagates changes throughout
 *      the calculation via the shift and XOR operations.
 *    - This diffusion property is what gives CRC its superior error detection capabilities
 *      compared to simpler checksums.
 *
 * 6. ERROR DETECTION CAPABILITIES:
 *    - Single-bit errors: Will always be detected because a change in any bit position
 *      propagates through the CRC calculation.
 *    - Two-bit errors: Will be detected as long as the erroneous bits are within the
 *      span of the polynomial degree (8 bits for CRC-8).
 *    - Odd number of bit errors: Always detected by any CRC.
 *    - Burst errors: CRC-8 can detect any burst errors up to 8 bits in length.
 *
 * 7. COMPARISON WITH OTHER CHECKSUMS:
 *    - Sum checksum: Simply adds all bytes, detecting only errors that don't sum to zero.
 *    - XOR checksum: XORs all bytes, failing when the same bit positions change an even number of times.
 *    - CRC-8: Uses polynomial division which creates a complex relationship between all input bits
 *      and the output checksum, making it much more robust against various error patterns.
 *
 * 8. PRACTICAL CONSIDERATIONS:
 *    - The polynomial (0x07) is chosen to maximize error detection capabilities for typical
 *      data patterns and error types.
 *    - While CRC-8 is not as robust as CRC-16 or CRC-32, it provides a good balance between
 *      error detection capability and computational/storage overhead for applications
 *      where space is limited but some error detection is needed.
 */

/*
 * FULL SAMPLE OUTPUT
 * =================
 * 
 * =============================================
 *    UNDERSTANDING CRC-8 CHECKSUM ALGORITHM    
 * =============================================
 * 
 * WHAT IS CRC-8?
 * --------------
 * CRC-8 is an 8-bit Cyclic Redundancy Check algorithm used for error detection
 * in digital networks and storage devices. It is more robust than simple checksums
 * like sum or XOR, and can detect more types of errors.
 * 
 * The algorithm uses a polynomial for division (in our case x^8 + x^2 + x + 1,
 * which is represented as 0x07 in binary). This polynomial creates a mathematical
 * relationship between all bits in the data that helps detect various error patterns.
 * 
 * WHY TWO CASES IN THE ALGORITHM?
 * ------------------------------
 * The two cases in the inner loop of the algorithm represent two different scenarios
 * in the CRC polynomial division process:
 * 
 * 1. When MSB is 1 (crc & 0x80):
 *    This means we need to perform polynomial division. We shift left (multiply by x)
 *    and then XOR with the polynomial (0x07). This XOR operation is equivalent to
 *    modulo-2 division in polynomial arithmetic.
 * 
 * 2. When MSB is 0:
 *    No division is needed, we just shift left (multiply by x). In modulo-2 division,
 *    you only XOR (subtract) when the bit aligns with a '1' in the dividend.
 * 
 * These two cases implement modulo-2 polynomial division, which is the mathematical
 * foundation of CRC algorithms.
 * 
 * Example 1: Simple data [0x01, 0x02]
 * =====================================
 * Step-by-step CRC-8 calculation for data: 0x1 0x2 
 * 
 * Initialize CRC = 0x00
 * 
 * Processing byte 1: Input byte: 0b00000001 (0x01)
 *   XOR with current CRC
 *   Current CRC: 0b00000000 (0x00)
 *   After XOR: 0b00000001 (0x01)
 *   Processing each bit:
 *     Bit 1:     Current CRC: 0b00000001 (0x01)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00000010 (0x02)
 *     Bit 2:     Current CRC: 0b00000010 (0x02)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00000100 (0x04)
 *     Bit 3:     Current CRC: 0b00000100 (0x04)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00001000 (0x08)
 *     Bit 4:     Current CRC: 0b00001000 (0x08)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00010000 (0x10)
 *     Bit 5:     Current CRC: 0b00010000 (0x10)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00100000 (0x20)
 *     Bit 6:     Current CRC: 0b00100000 (0x20)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b01000000 (0x40)
 *     Bit 7:     Current CRC: 0b01000000 (0x40)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b10000000 (0x80)
 *     Bit 8:     Current CRC: 0b10000000 (0x80)
 *     MSB is 1 (crc & 0x80 is true) --> Shift left and XOR with polynomial 0x07
 *       After shift: 0b00000000 (0x00)
 *       Polynomial: 0b00000111 (0x07)
 *       Result: 0b00000111 (0x07)
 * 
 * Processing byte 2: Input byte: 0b00000010 (0x02)
 *   XOR with current CRC
 *   Current CRC: 0b00000111 (0x07)
 *   After XOR: 0b00000101 (0x05)
 *   Processing each bit:
 *     Bit 1:     Current CRC: 0b00000101 (0x05)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00001010 (0x0a)
 *     Bit 2:     Current CRC: 0b00001010 (0x0a)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00010100 (0x14)
 *     Bit 3:     Current CRC: 0b00010100 (0x14)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00101000 (0x28)
 *     Bit 4:     Current CRC: 0b00101000 (0x28)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b01010000 (0x50)
 *     Bit 5:     Current CRC: 0b01010000 (0x50)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b10100000 (0xa0)
 *     Bit 6:     Current CRC: 0b10100000 (0xa0)
 *     MSB is 1 (crc & 0x80 is true) --> Shift left and XOR with polynomial 0x07
 *       After shift: 0b01000000 (0x40)
 *       Polynomial: 0b00000111 (0x07)
 *       Result: 0b01000111 (0x47)
 *     Bit 7:     Current CRC: 0b01000111 (0x47)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b10001110 (0x8e)
 *     Bit 8:     Current CRC: 0b10001110 (0x8e)
 *     MSB is 1 (crc & 0x80 is true) --> Shift left and XOR with polynomial 0x07
 *       After shift: 0b00011100 (0x1c)
 *       Polynomial: 0b00000111 (0x07)
 *       Result: 0b00011011 (0x1b)
 * 
 * Final CRC-8 checksum: : 0b00011011 (0x1b)
 * 
 * 
 * Example 2: ASCII data 'AB' [0x41, 0x42]
 * ==========================================
 * Step-by-step CRC-8 calculation for data: 0x41 0x42 
 * 
 * Initialize CRC = 0x00
 * 
 * Processing byte 1: Input byte: 0b01000001 (0x41)
 *   XOR with current CRC
 *   Current CRC: 0b00000000 (0x00)
 *   After XOR: 0b01000001 (0x41)
 *   Processing each bit:
 *     Bit 1:     Current CRC: 0b01000001 (0x41)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b10000010 (0x82)
 *     Bit 2:     Current CRC: 0b10000010 (0x82)
 *     MSB is 1 (crc & 0x80 is true) --> Shift left and XOR with polynomial 0x07
 *       After shift: 0b00000100 (0x04)
 *       Polynomial: 0b00000111 (0x07)
 *       Result: 0b00000011 (0x03)
 *     Bit 3:     Current CRC: 0b00000011 (0x03)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00000110 (0x06)
 *     Bit 4:     Current CRC: 0b00000110 (0x06)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00001100 (0x0c)
 *     Bit 5:     Current CRC: 0b00001100 (0x0c)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00011000 (0x18)
 *     Bit 6:     Current CRC: 0b00011000 (0x18)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00110000 (0x30)
 *     Bit 7:     Current CRC: 0b00110000 (0x30)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b01100000 (0x60)
 *     Bit 8:     Current CRC: 0b01100000 (0x60)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b11000000 (0xc0)
 * 
 * Processing byte 2: Input byte: 0b01000010 (0x42)
 *   XOR with current CRC
 *   Current CRC: 0b11000000 (0xc0)
 *   After XOR: 0b10000010 (0x82)
 *   Processing each bit:
 *     Bit 1:     Current CRC: 0b10000010 (0x82)
 *     MSB is 1 (crc & 0x80 is true) --> Shift left and XOR with polynomial 0x07
 *       After shift: 0b00000100 (0x04)
 *       Polynomial: 0b00000111 (0x07)
 *       Result: 0b00000011 (0x03)
 *     Bit 2:     Current CRC: 0b00000011 (0x03)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00000110 (0x06)
 *     Bit 3:     Current CRC: 0b00000110 (0x06)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00001100 (0x0c)
 *     Bit 4:     Current CRC: 0b00001100 (0x0c)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00011000 (0x18)
 *     Bit 5:     Current CRC: 0b00011000 (0x18)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b00110000 (0x30)
 *     Bit 6:     Current CRC: 0b00110000 (0x30)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b01100000 (0x60)
 *     Bit 7:     Current CRC: 0b01100000 (0x60)
 *     MSB is 0 (crc & 0x80 is false) --> Just shift left
 *       Result: 0b11000000 (0xc0)
 *     Bit 8:     Current CRC: 0b11000000 (0xc0)
 *     MSB is 1 (crc & 0x80 is true) --> Shift left and XOR with polynomial 0x07
 *       After shift: 0b10000000 (0x80)
 *       Polynomial: 0b00000111 (0x07)
 *       Result: 0b10000111 (0x87)
 * 
 * Final CRC-8 checksum: : 0b10000111 (0x87)
 * 
 * 
 * COMPARISON WITH SIMPLER CHECKSUMS
 * =================================
 * Simple checksum comparisons:
 * Sum checksum: 0b10000011 (0x83)
 * XOR checksum: 0b00000011 (0x03)
 * CRC-8 checksum: 0b10000111 (0x87)
 * 
 * 
 * ERROR DETECTION CAPABILITIES
 * ===========================
 * 
 * *** ERROR DETECTION COMPARISON ***
 * Original data: 'Hello'
 * Error 1 (1-bit): 'Hemlo'
 * Error 2 (swapped): 'Helol'
 * Error 3 (multi-bit): 'HEllo'
 * 
 * Sum checksum:
 * Original: 0xf4
 * Error 1: 0xf5 (detected)
 * Error 2: 0xf4 (UNDETECTED!)
 * Error 3: 0xd4 (detected)
 * 
 * XOR checksum:
 * Original: 0x42
 * Error 1: 0x43 (detected)
 * Error 2: 0x42 (UNDETECTED!)
 * Error 3: 0x62 (detected)
 * 
 * CRC-8 checksum:
 * Original: 0xf6
 * Error 1: 0x9d (detected)
 * Error 2: 0xc0 (detected)
 * Error 3: 0x38 (detected)
 * 
 * 
 * WHY CRC-8 IS BETTER THAN SIMPLE CHECKSUMS
 * --------------------------------------
 * 1. Bit Sensitivity: CRC is highly sensitive to changes in any bit position
 *    because each bit affects the polynomial division process.
 * 
 * 2. Error Detection Capabilities:
 *    - Detects all single-bit errors
 *    - Detects all double-bit errors for certain message lengths
 *    - Detects any odd number of bit errors
 *    - Detects burst errors of length <= 8 bits
 *    - Detects most longer burst errors with high probability
 * 
 * 3. Simple checksums fail in many common error scenarios:
 *    - Sum checksum: Fails if errors cancel out (e.g., +1 in one byte, -1 in another)
 *    - XOR checksum: Fails if the same bit positions are changed in an even number of bytes
 *    - Both fail to detect byte swaps, as the order doesn't matter to them
 * 
 * 4. Mathematical Foundation: CRC has a strong mathematical foundation (polynomial algebra)
 *    that makes its error detection properties theoretically provable.
 */
