#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "_FileHandler.h"

int main() {
    // Example usage
    std::string csvFilename = "data.csv";
    std::vector<std::vector<std::string> > csvData;
    
    std::vector<std::string> row1;
    row1.push_back("Name");
    row1.push_back("Age");
    row1.push_back("City");
    csvData.push_back(row1);
    
    std::vector<std::string> row2;
    row2.push_back("John Doe");
    row2.push_back("25");
    row2.push_back("New York");
    csvData.push_back(row2);
    
    std::vector<std::string> row3;
    row3.push_back("Jane Smith");
    row3.push_back("30");
    row3.push_back("London");
    csvData.push_back(row3);

    // Write data to CSV file
    FileHandler::writeCSV(csvFilename, csvData);

    // Read data from CSV file
    std::vector<std::vector<std::string> > readData = FileHandler::readCSV(csvFilename);
    for (const std::vector<std::string>& row : readData) {
        for (const std::string& value : row) {
            std::cout << value << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    // Example usage for text file
    std::string textFilename = "data.txt";
    std::string textContent = "This is some example text.";

    // Write data to text file
    FileHandler::writeText(textFilename, textContent);

    // Read data from text file
    std::string readText = FileHandler::readText(textFilename);
    std::cout << readText << std::endl;

    return 0;
}