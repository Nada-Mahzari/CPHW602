/*
Write a Python script that performs the following tasks:

1. Read Data:

Write a function named read_from_file(filename) that takes a filename as input and reads the contents of the file. The function should return a list of strings, where each string represents a line from the file.

2. Main Script:

A. Use the read_from_file("fruits.txt") function to read the contents of a file named "fruits.txt", which contains a list of fruits, each on a new line.
B. Print each fruit to the console.
Make sure the script correctly reads and prints the contents of the "fruits.txt" file.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void Q8() {
    // Function to read data from the file
    std::ifstream file("fruits.txt");  // Open the file "fruits.txt"

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::vector<std::string> fruits;  // Vector to store the fruits
    std::string line;

    // Read lines from the file and store them in the vector
    while (std::getline(file, line)) {
        fruits.push_back(line);  // Add each line (fruit) to the vector
    }

    // Close the file
    file.close();

    // Print each fruit in the vector
    for (const std::string& fruit : fruits) {
        std::cout << fruit << std::endl;  // Print each fruit
    }
}

