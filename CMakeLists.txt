cmake_minimum_required(VERSION 3.14)

set(this Final_Project)
project(${this} CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

# Google Test setup
add_subdirectory(googletest)

# Header files
set(Headers
    include/HammingEncoder.h
    include/HammingDecoder.h
    include/FileHandler.h
)

# Source files
set(Sources
    HammingEncoder.cpp
    HammingDecoder.cpp
    FileHandler.cpp
)

# Add library
add_library(${this} SHARED ${Sources} ${Headers})
target_include_directories(${this} PUBLIC include)

# Testing executable
set(test Final_Project_testing)
set(testSources
    testHamming.cpp
)

add_executable(${test} ${testSources})
target_link_libraries(${test} PUBLIC
    gtest_main
    ${this}
)

add_test(
    NAME ${test}
    COMMAND ${test}
)
