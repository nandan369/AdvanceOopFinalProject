#ifndef HAMMING_ENCODER_H
#define HAMMING_ENCODER_H

#include <vector>

/**
 * @class HammingEncoder
 * @brief A class for encoding data using the Hamming code technique.
 *
 * The HammingEncoder class provides methods to encode data using a predefined
 * generator matrix for error detection and correction. The class initializes
 * the generator matrix automatically upon creation.
 */
class HammingEncoder {
public:
    /**
     * @brief Constructs a HammingEncoder object.
     *
     * Initializes the generator matrix required for encoding operations.
     */
    HammingEncoder();

    /**
     * @brief Encodes a vector of data bits using the Hamming code.
     *
     * This function takes a vector of data bits and applies the Hamming code
     * algorithm to generate encoded bits that include error detection and correction.
     *
     * @param data A vector of integers representing the input data bits (0s and 1s).
     * @return A vector of integers representing the encoded data bits.
     */
    std::vector<int> encode(const std::vector<int>& data) const;

private:
    /**
     * @brief The generator matrix used for encoding.
     *
     * This matrix is initialized during the construction of the HammingEncoder object.
     * It is used to calculate the encoded bits.
     */
    std::vector<std::vector<int>> generatorMatrix;

    /**
     * @brief Initializes the generator matrix for the Hamming code.
     *
     * This function is called during object construction to set up the generator
     * matrix needed for encoding operations.
     */
    void initializeGeneratorMatrix();
};

#endif
