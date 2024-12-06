#include "HammingEncoder.h"
#include <iostream>
#include <stdexcept> // For std::invalid_argument

/**
 * @brief Constructs a HammingEncoder object and initializes the generator matrix.
 *
 * The constructor calls the `initializeGeneratorMatrix` method to set up
 * the generator matrix required for Hamming code encoding.
 */
HammingEncoder::HammingEncoder() {
    initializeGeneratorMatrix();
}

/**
 * @brief Initializes the generator matrix for the (7, 4) Hamming Code.
 *
 * The generator matrix is predefined for a (7, 4) Hamming Code, which maps 4 data bits
 * to 7 encoded bits with error detection and correction capabilities.
 */
void HammingEncoder::initializeGeneratorMatrix() {
    // Initialize the generator matrix for (7, 4) Hamming Code
    generatorMatrix = {
        {1, 0, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 1, 1}
    };
}

/**
 * @brief Encodes a 4-bit data vector using the (7, 4) Hamming Code.
 *
 * This function takes a 4-bit input vector, performs matrix multiplication with
 * the generator matrix (modulo 2), and produces a 7-bit encoded vector.
 *
 * @param data A vector of integers representing the 4-bit input data (0s and 1s).
 * @return A vector of integers representing the 7-bit encoded data.
 * 
 * @throws std::invalid_argument if the input vector does not contain exactly 4 bits.
 */
std::vector<int> HammingEncoder::encode(const std::vector<int>& data) const {
    // Check if the input has exactly 4 bits
    if (data.size() != 4) {
        throw std::invalid_argument("Input data must have exactly 4 bits.");
    }

    std::vector<int> encoded(7, 0); // Initialize encoded data vector with 7 bits

    // Perform matrix multiplication (mod 2) for encoding
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 7; ++j) {
            encoded[j] ^= (data[i] * generatorMatrix[i][j]);  // XOR for modulo-2
        }
    }

    return encoded;
}
