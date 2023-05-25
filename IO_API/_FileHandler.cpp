#include "_FileHandler.h"

// Read data from a CSV file and store it in a 2D vector
std::vector<std::vector<std::string> > FileHandler::readCSV(const std::string& filename) {
    std::vector<std::vector<std::string> > data;
    std::ifstream file(filename);
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> row;
            std::istringstream iss(line);
            std::string value;
            while (std::getline(iss, value, ',')) {
                row.push_back(value);
            }
            data.push_back(row);
        }
        file.close();
    }
    return data;
}

// Write data to a CSV file from a 2D vector
void FileHandler::writeCSV(const std::string& filename, const std::vector<std::vector<std::string> >& data) {
    std::ofstream file(filename);
    if (file) {
        for (const std::vector<std::string>& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i != row.size() - 1) {
                    file << ",";
                }
            }
            file << std::endl;
        }
        file.close();
    }
}

// Read data from a text file and return it as a string
std::string FileHandler::readText(const std::string& filename) {
    std::ifstream file(filename);
    std::string content;
    if (file) {
        std::ostringstream oss;
        oss << file.rdbuf();
        content = oss.str();
        file.close();
    }
    return content;
}

// Write data to a text file
void FileHandler::writeText(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (file) {
        file << content;
        file.close();
    }
}