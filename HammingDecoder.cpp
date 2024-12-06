#include "HammingDecoder.h"
#include <iostream>
#include <stdexcept>

/**
 * @brief Constructor for HammingDecoder class.
 *
 * Initializes the parity check matrix by calling the initializeParityCheckMatrix method.
 */
HammingDecoder::HammingDecoder() {
    initializeParityCheckMatrix();
}

/**
 * @brief Initializes the parity-check matrix for the (7, 4) Hamming Code.
 *
 * This matrix is used to detect and correct single-bit errors in the encoded data.
 * The matrix represents the relationships between the parity bits and the data bits.
 */
void HammingDecoder::initializeParityCheckMatrix() {
    parityCheckMatrix = {
        {1, 0, 1, 0, 1, 0, 1},
        {0, 1, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 1, 1}
    };
}

/**
 * @brief Calculates the syndrome of the encoded data using the parity check matrix.
 *
 * The syndrome is computed as the modulo-2 dot product of the transpose of the parity check matrix (H^T)
 * and the encoded data. A non-zero syndrome indicates the presence of errors.
 *
 * @param encodedData A vector representing the encoded data (7 bits).
 * @return A vector containing the 3-bit syndrome.
 */
std::vector<int> HammingDecoder::calculateSyndrome(const std::vector<int>& encodedData) {
    std::vector<int> syndrome(3, 0);  //!< Initialize syndrome vector to all 0s
    
    // Iterate over rows of H (parity check matrix)
    for (int i = 0; i < 3; ++i) {  
        // Iterate over columns of H (encoded data bits)
        for (int j = 0; j < 7; ++j) {  
            syndrome[i] ^= (encodedData[j] * parityCheckMatrix[i][j]);  // XOR the product for modulo-2
        }
    }

    return syndrome;  // Returns a 3-bit syndrome that indicates error position if non-zero
}

/**
 * @brief Decodes the Hamming (7, 4) codeword and corrects single-bit errors.
 *
 * This method checks if the encoded data contains any single-bit errors. If errors are found, it corrects them 
 * and returns the corrected data (first 4 bits). If no errors are detected, it returns the original data.
 *
 * @param encodedData A vector representing the encoded data (7 bits).
 * @return A vector containing the decoded 4-bit data after error correction, or an empty vector if errors cannot be corrected.
 * @throws std::invalid_argument if the encoded data does not contain exactly 7 bits.
 */
std::vector<int> HammingDecoder::decode(const std::vector<int>& encodedData) {
    // Validate the encoded data length
    if (encodedData.size() != 7) {
        throw std::invalid_argument("Encoded data must have 7 bits.");
    }

    std::vector<int> syndrome = calculateSyndrome(encodedData);  //!< Calculate the syndrome

    // Print the encoded data and syndrome
    std::cout << "Encoded Data: ";
    for (int bit : encodedData) std::cout << bit;
    std::cout << "\nSyndrome: ";
    for (int s : syndrome) std::cout << s;
    std::cout << std::endl;

    // Check if no error (syndrome is 000)
    if (syndrome[0] == 0 && syndrome[1] == 0 && syndrome[2] == 0) {
        std::cout << "Decoded Data: ";
        for (auto it = encodedData.begin(); it != encodedData.begin() + 4; ++it)
            std::cout << *it;
        std::cout << " (no correction needed)\n";
        return std::vector<int>(encodedData.begin(), encodedData.begin() + 4);  //!< Return the first 4 bits if no correction needed
    }

    // Calculate the error position (1-based index)
    int errorPosition = syndrome[0] * 1 + syndrome[1] * 2 + syndrome[2] * 4;

    // Check for multiple errors or invalid error position
    if (errorPosition < 1 || errorPosition > 7) {
        std::cerr << "Error: Syndrome indicates invalid or multiple error positions.\n";
        return {};  //!< Return empty vector to indicate an uncorrectable error
    }

    // Flip the erroneous bit at the calculated position (correct single-bit error)
    std::vector<int> correctedData = encodedData;
    correctedData[errorPosition - 1] ^= 1;  //!< Flip the bit at the error position

    // Print the corrected data and indicate which bit was corrected
    std::cout << "Decoded Data: ";
    for (auto it = correctedData.begin(); it != correctedData.begin() + 4; ++it)
        std::cout << *it;
    std::cout << " (corrected bit at position: " << errorPosition << ")\n";

    // Return the corrected first 4 bits as the decoded data
    return std::vector<int>(correctedData.begin(), correctedData.begin() + 4);
}