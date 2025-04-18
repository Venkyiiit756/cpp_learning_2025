/*
 * checksums.cpp
 * -------------
 * Demonstrates several common checksum algorithms in C++.
 * Each function is explained and shown with example data.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint> // Added for uint8_t

// 1. Simple Sum Checksum
// Sums all bytes in the data. Not robust, but very fast.
uint8_t sum_checksum(const std::vector<uint8_t>& data) {
    uint32_t sum = 0;
    for (uint8_t byte : data) {
        sum += byte;
    }
    // Return only the least significant byte
    return static_cast<uint8_t>(sum & 0xFF);
}

// 2. XOR Checksum
// XORs all bytes together. Good at detecting single-bit errors.
uint8_t xor_checksum(const std::vector<uint8_t>& data) {
    uint8_t result = 0;
    for (uint8_t byte : data) {
        result ^= byte;
    }
    return result;
}

// 3. CRC-8 (Cyclic Redundancy Check, 8-bit)
// More robust than sum or XOR. Uses a polynomial for error detection.
// Here we use the polynomial x^8 + x^2 + x + 1 (0x07).
uint8_t crc8_checksum(const std::vector<uint8_t>& data) {
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

int main() {
    // Example data for checksum calculation
    std::vector<uint8_t> data = {0x10, 0x20, 0x30, 0x40, 0x55, 0xAA, 0xFF};

    std::cout << "Data bytes: ";
    for (auto b : data)
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)b << " ";
    std::cout << std::dec << std::endl;

    // 1. Simple Sum Checksum
    uint8_t sum = sum_checksum(data);
    std::cout << "Simple Sum Checksum: 0x" << std::hex << (int)sum << std::dec << std::endl;

    // 2. XOR Checksum
    uint8_t xsum = xor_checksum(data);
    std::cout << "XOR Checksum: 0x" << std::hex << (int)xsum << std::dec << std::endl;

    // 3. CRC-8 Checksum
    uint8_t crc = crc8_checksum(data);
    std::cout << "CRC-8 Checksum: 0x" << std::hex << (int)crc << std::dec << std::endl;

    /*
     * Output will show:
     * - The data bytes
     * - The result of each checksum
     * 
     * You can change the data to see how each checksum responds to changes.
     */
    return 0;
}
