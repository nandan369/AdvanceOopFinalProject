#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Reads encoded data from a file.
 *
 * This method reads a file containing lines of 7-bit encoded words.
 * Each line in the file must contain exactly 7 bits (0s and 1s).
 * Lines that do not meet this criterion are skipped with an error message.
 *
 * @param filename The name of the file to read the encoded data from.
 * @return A 2D vector of integers where each sub-vector represents a 7-bit encoded word.
 */
std::vector<std::vector<int>> FileHandler::readEncodedFile(const std::string& filename) const {
    std::vector<std::vector<int>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for reading." << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.size() != 7 || line.find_first_not_of("01") != std::string::npos) {
            std::cerr << "Error: Invalid line in file: " << line << std::endl;
            continue;
        }

        std::vector<int> encodedWord;
        for (char c : line) {
            encodedWord.push_back(c - '0'); // Convert character '0' or '1' to integer 0 or 1
        }
        data.push_back(encodedWord);
    }

    return data;
}

/**
 * @brief Writes decoded data to a file.
 *
 * This method writes a 2D vector of decoded data to the specified file.
 * Each sub-vector is written as a line, with the bits concatenated.
 *
 * @param filename The name of the file to write the decoded data to.
 * @param decodedData A 2D vector of integers where each sub-vector represents a decoded word.
 */
void FileHandler::writeDecodedFile(const std::string& filename, const std::vector<std::vector<int>>& decodedData) const {
    std::ofstream file(filename);
    
    if (!file) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    for (const auto& word : decodedData) {
        for (int bit : word) {
            file << bit; // Write each bit to the file
        }
        file << std::endl; // New line after each word
    }
}
