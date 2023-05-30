#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class FileHandler {
public:
    // Read data from a CSV file and store it in a 2D vector
    static std::vector<std::vector<std::string> > readCSV(const std::string& filename);

    // Write data to a CSV file from a 2D vector
    static void writeCSV(const std::string& filename, const std::vector<std::vector<std::string> >& data);

    // Read data from a text file and return it as a string
    static std::string readText(const std::string& filename);

    // Write data to a text file
    static void writeText(const std::string& filename, const std::string& content);

     std::string getConfigValue(const std::string& parameter);
};

#endif // FILE_HANDLER_H