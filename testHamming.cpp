#include "HammingEncoder.h"
#include "HammingDecoder.h"
#include "FileHandler.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

// ----- HammingEncoder Tests -----
TEST(HammingEncoderTest, EncodeValidInput) {
    HammingEncoder encoder;
    std::vector<int> data = {1, 0, 1, 1};
    std::vector<int> encoded = encoder.encode(data);
    EXPECT_EQ(encoded, (std::vector<int>{1, 0, 1, 1, 0, 1, 1}));
}

TEST(HammingEncoderTest, EncodeAllZeros) {
    HammingEncoder encoder;
    std::vector<int> data = {0, 0, 0, 0};
    std::vector<int> encoded = encoder.encode(data);
    EXPECT_EQ(encoded, (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
}

TEST(HammingEncoderTest, EncodeAllOnes) {
    HammingEncoder encoder;
    std::vector<int> data = {1, 1, 1, 1};
    std::vector<int> encoded = encoder.encode(data);
    EXPECT_EQ(encoded, (std::vector<int>{1, 1, 1, 1, 0, 0, 0}));
}

TEST(HammingEncoderTest, EncodeInvalidLengthInput) {
    HammingEncoder encoder;
    std::vector<int> invalidInput = {1, 0, 1};
    EXPECT_THROW(encoder.encode(invalidInput), std::invalid_argument);
}

// ----- HammingDecoder Tests -----

TEST(HammingDecoderTest, CalculateSyndromeNoError) {
    HammingDecoder decoder;
    std::vector<int> encoded = {1, 0, 1, 1, 0, 1, 1};
    std::vector<int> syndrome = decoder.calculateSyndrome(encoded);
    EXPECT_EQ(syndrome, (std::vector<int>{0, 0, 0}));
}

TEST(HammingDecoderTest, CalculateSyndromeWithError) {
    HammingDecoder decoder;
    std::vector<int> encoded = {1, 0, 1, 1, 0, 1, 0};  // Error in last bit
    std::vector<int> syndrome = decoder.calculateSyndrome(encoded);
    EXPECT_EQ(syndrome, (std::vector<int>{0, 0, 1}));
}

TEST(HammingDecoderTest, DecodeNoError) {
    HammingDecoder decoder;
    std::vector<int> encoded = {1, 0, 1, 1, 0, 1, 1};
    std::vector<int> decoded = decoder.decode(encoded);
    EXPECT_EQ(decoded, (std::vector<int>{1, 0, 1, 1}));
}

TEST(HammingDecoderTest, DecodeWithSingleBitError) {
    HammingDecoder decoder;
    std::vector<int> encoded = {1, 0, 1, 1, 0, 1, 0};  // Error in last bit
    std::vector<int> decoded = decoder.decode(encoded);
    EXPECT_EQ(decoded, (std::vector<int>{1, 0, 1, 1}));
}

TEST(HammingDecoderTest, DecodeInvalidErrorPosition) {
    HammingDecoder decoder;
    std::vector<int> encoded = {1, 0, 1, 1, 1, 1, 1};  // Invalid error position
    auto decoded = decoder.decode(encoded);
    EXPECT_TRUE(decoded.empty());
}

TEST(HammingDecoderTest, DecodeInvalidLengthEncodedData) {
    HammingDecoder decoder;
    std::vector<int> invalidEncodedData = {1, 0, 1, 0, 1};  // Length not 7
    EXPECT_THROW(decoder.decode(invalidEncodedData), std::invalid_argument);
}

TEST(HammingDecoderTest, DecodeAllErrors) {
    HammingDecoder decoder;
    std::vector<int> allFlippedData = {1, 1, 1, 1, 1, 1, 1};  // All bits flipped
    auto decoded = decoder.decode(allFlippedData);
    EXPECT_TRUE(decoded.empty());
}

// ----- FileHandler Tests -----
class FileHandlerTest : public ::testing::Test {
protected:
    FileHandler fileHandler;
    std::string testReadFile = "test_read.txt";
    std::string testWriteFile = "test_write.txt";
};

TEST_F(FileHandlerTest, ReadValidEncodedFile) {
    std::ofstream outFile(testReadFile);
    outFile << "1011011\n0010010\n";
    outFile.close();

    auto data = fileHandler.readEncodedFile(testReadFile);
    EXPECT_EQ(data.size(), 2);
    EXPECT_EQ(data[0], (std::vector<int>{1, 0, 1, 1, 0, 1, 1}));
}

TEST_F(FileHandlerTest, ReadFileWithInvalidLines) {
    std::ofstream outFile(testReadFile);
    outFile << "1011011\nINVALID\n";
    outFile.close();

    auto data = fileHandler.readEncodedFile(testReadFile);
    EXPECT_EQ(data.size(), 1);  // Only 1 valid line
}

TEST_F(FileHandlerTest, ReadNonExistentFile) {
    auto data = fileHandler.readEncodedFile("nonexistent.txt");
    EXPECT_TRUE(data.empty());
}

TEST_F(FileHandlerTest, WriteDecodedFile) {
    std::vector<std::vector<int>> decodedData = {{1, 0, 1, 1}, {0, 1, 0, 0}};
    fileHandler.writeDecodedFile(testWriteFile, decodedData);

    std::ifstream inFile(testWriteFile);
    std::string line;
    std::getline(inFile, line);
    EXPECT_EQ(line, "1011");
}

TEST_F(FileHandlerTest, WriteToInvalidPath) {
    std::vector<std::vector<int>> decodedData = {{1, 0, 1, 1}};
    EXPECT_NO_THROW(fileHandler.writeDecodedFile("/invalid_path/output.txt", decodedData));
}

TEST_F(FileHandlerTest, ReadEmptyFile) {
    std::ofstream outFile(testReadFile);
    outFile.close();  // Create an empty file

    auto data = fileHandler.readEncodedFile(testReadFile);
    EXPECT_TRUE(data.empty());
}

TEST_F(FileHandlerTest, WriteEmptyData) {
    std::vector<std::vector<int>> emptyData;
    fileHandler.writeDecodedFile(testWriteFile, emptyData);

    std::ifstream inFile(testWriteFile);
    std::string line;
    EXPECT_FALSE(std::getline(inFile, line));  // File should be empty
}
