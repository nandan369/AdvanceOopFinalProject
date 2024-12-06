// main.cpp
#include "HammingEncoder.h"
#include "HammingDecoder.h"
#include "FileHandler.h"
#include <iostream>
#include <vector>
#include <stdexcept>

int main() {
    // Specify the filenames for reading and writing
    std::string inputFile = "encoded_data.txt";
    std::string outputFile = "decoded_data.txt";

    // Create instances of the FileHandler, HammingEncoder, and HammingDecoder
    FileHandler fileHandler;
    HammingEncoder encoder;  // Make sure you have this class implemented somewhere
    HammingDecoder decoder;

    // Read encoded data from the input file
    std::vector<std::vector<int>> encodedData = fileHandler.readEncodedFile(inputFile);

    if (encodedData.empty()) {
        std::cerr << "No valid encoded data found in the file." << std::endl;
        return 1;
    }

    // Vector to store decoded data
    std::vector<std::vector<int>> decodedData;

    // Process each encoded word
    for (const auto& encodedWord : encodedData) {
        try {
            // Decode the 7-bit encoded word
            std::vector<int> decodedWord = decoder.decode(encodedWord);

            // If decoding is successful, add the decoded word to the result
            if (!decodedWord.empty()) {
                decodedData.push_back(decodedWord);
            } else {
                std::cerr << "Failed to decode due to multiple errors in word." << std::endl;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error during decoding: " << e.what() << std::endl;
        }
    }

    // Write the decoded data to the output file
    fileHandler.writeDecodedFile(outputFile, decodedData);

    std::cout << "Decoded data has been written to " << outputFile << std::endl;

    return 0;
}
