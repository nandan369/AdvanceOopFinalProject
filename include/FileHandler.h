#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <vector>
#include <string>

/**
 * @class FileHandler
 * @brief A utility class for handling file operations related to encoded and decoded data.
 *
 * The FileHandler class provides methods to read encoded data from a file
 * and write decoded data back to a file. It supports operations with 2D vectors
 * of integers representing the data.
 */
class FileHandler {
public:
    /**
     * @brief Default constructor for the FileHandler class.
     *
     * Constructs a FileHandler object with no special initialization.
     */
    FileHandler() = default;

    /**
     * @brief Reads encoded data from a file.
     *
     * This function reads a file containing encoded data, parses it, and
     * returns the data as a 2D vector of integers. Each row in the file
     * corresponds to a vector of encoded bits.
     *
     * @param filename The name of the file to read the encoded data from.
     * @return A 2D vector of integers representing the encoded data.
     */
    std::vector<std::vector<int>> readEncodedFile(const std::string& filename) const;

    /**
     * @brief Writes decoded data to a file.
     *
     * This function writes a 2D vector of decoded data to a file. Each row
     * of the vector is written as a separate line in the file.
     *
     * @param filename The name of the file to write the decoded data to.
     * @param decodedData A 2D vector of integers representing the decoded data.
     */
    void writeDecodedFile(const std::string& filename, const std::vector<std::vector<int>>& decodedData) const;
};

#endif
