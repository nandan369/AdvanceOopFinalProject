# Variables
CXX = g++                    # The C++ compiler to use (g++)
OBJECTS = main.o HammingEncoder.o HammingDecoder.o FileHandler.o       # Object files that will be generated
FLAGS = -Wall -std=c++20 -I./include   # Add -I flag to specify the include directory
SOURCE = $(wildcard *.cpp)    # Finds all .cpp source files in the current directory
TARGET = hamming   # The name of the final executable

# Default target: Compile the project into an executable
all: $(TARGET)

# Target: Link the object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o $(TARGET)

# Pattern rule: Compile .cpp files into corresponding .o files
%.o: %.cpp
	$(CXX) -c $(FLAGS) $< -o $@  # Add $(FLAGS) to ensure the include directory is passed for each file

# Target: Compile and run the program
run: all
	./$(TARGET)

# Target: Display the list of source files (useful for debugging or checking sources)
echo:
	echo $(SOURCE)

# Target: Clean up by removing the object files and the executable
clean:
	rm -f $(OBJECTS) $(TARGET)
