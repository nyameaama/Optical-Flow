#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

class FileHandler {
private:
    // Read data from a CSV file and store it in a 2D vector
    static std::vector<std::vector<std::string> > readCSV(const std::string& filename);

    // Read data from a text file and return it as a string
    static std::string readText(const std::string& filename);

    // Write data to a text file
    static void writeText(const std::string& filename, const std::string& content);

public:
    std::string getConfigValue(const std::string& parameter);
    
    // Write data to a CSV file from a 2D vector
    void writeToCSV(const std::string& filename, int row, int col, const std::string& data);
};

#endif // FILE_HANDLER_H