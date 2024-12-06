#ifndef HAMMING_DECODER_H
#define HAMMING_DECODER_H

#include <vector>

/**
 * @class HammingDecoder
 * @brief A class for decoding data encoded with Hamming codes.
 *
 * The HammingDecoder class provides methods to decode data, check for errors,
 * and calculate syndromes to identify and correct single-bit errors. It utilizes
 * a parity-check matrix for these operations.
 */
class HammingDecoder {
public:
    /**
     * @brief Constructs a HammingDecoder object.
     *
     * Initializes the parity-check matrix required for decoding operations.
     */
    HammingDecoder();

    /**
     * @brief Decodes a vector of encoded data bits.
     *
     * This function decodes the input encoded data, corrects any single-bit errors,
     * and returns the original data bits.
     *
     * @param encodedData A vector of integers representing the encoded data bits (0s and 1s).
     * @return A vector of integers representing the decoded data bits.
     */
    std::vector<int> decode(const std::vector<int>& encodedData);

    /**
     * @brief Checks if the calculated syndrome indicates multiple errors.
     *
     * This function analyzes the syndrome to determine if multiple errors
     * exist in the encoded data, which cannot be corrected by the Hamming code.
     *
     * @param syndrome A vector of integers representing the calculated syndrome.
     * @return `true` if multiple errors are detected; `false` otherwise.
     */
    bool hasMultipleErrors(const std::vector<int>& syndrome);

    /**
     * @brief Calculates the syndrome for the given encoded data.
     *
     * The syndrome is calculated using the parity-check matrix and provides
     * information about error positions in the encoded data.
     *
     * @param encodedData A vector of integers representing the encoded data bits (0s and 1s).
     * @return A vector of integers representing the calculated syndrome.
     */
    std::vector<int> calculateSyndrome(const std::vector<int>& encodedData);

private:
    /**
     * @brief The parity-check matrix used for error detection and correction.
     *
     * This matrix is initialized during the construction of the HammingDecoder object.
     */
    std::vector<std::vector<int>> parityCheckMatrix;

    /**
     * @brief Initializes the parity-check matrix for Hamming code decoding.
     *
     * This function sets up the matrix used to calculate syndromes and identify errors.
     */
    void initializeParityCheckMatrix();
};

#endif
