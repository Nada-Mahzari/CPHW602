/*
Write a Python script that performs the following tasks:

1. Create Data:

Create a list of strings: ["apple", "banana", "cherry"].

2. Save Data:

Write a function named save_to_file(data, filename) that takes a list of strings and a filename as input and writes each string to a new line in a text file with the given filename.

3. Main Script:

Use the save_to_file(data, "fruits.txt") function to save the list of strings to a text file named "fruits.txt".
Ensure that the script creates the file and writes the strings correctly.

*/




#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void saveToFile(const std::vector<std::string>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& item : data) {
            file << item << "\n";
        }
        file.close();
        std::cout << "Data has been saved to " << filename << "." << std::endl;
    } else {
        std::cerr << "Error: Unable to open the file " << filename << "." << std::endl;
    }
}

int main() {

    std::vector<std::string> data = {"apple", "banana", "cherry"};


    saveToFile(data, "fruits.txt");

    return 0;
}














