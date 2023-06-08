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

// Write data to a CSV file 
void FileHandler::writeToCSV(const std::string& filename, int row, int col, const std::string& data) {
    std::ifstream inputFile(filename);  // Open the file for reading

    // Check if the file exists
    bool fileExists = inputFile.good();
    inputFile.close();

    // Create a vector of strings to store each row
    std::vector<std::string> rows;

    if (fileExists) {
        // Read the existing file line by line and store each line in the vector
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            rows.push_back(line);
        }
        file.close();
    }

    // Check if the row exists
    if (row < rows.size()) {
        // Append the data to the specific column of the existing row
        std::istringstream iss(rows[row]);
        std::vector<std::string> colValues(std::istream_iterator<std::string>{iss},
                                           std::istream_iterator<std::string>());

        // Check if the column exists
        if (col < colValues.size()) {
            colValues[col] = data;
        } else {
            // Append empty values until the desired column is reached
            while (colValues.size() < col) {
                colValues.push_back("");
            }
            colValues.push_back(data);
        }

        // Update the modified row in the vector
        rows[row] = "";
        for (const auto& value : colValues) {
            rows[row] += value + ",";
        }
        // Remove the trailing comma
        rows[row].pop_back();
    } else {
        // Append empty rows until the desired row is reached
        while (rows.size() < row) {
            rows.push_back("");
        }

        // Append the data in the new row
        std::string newRow = "";
        for (int i = 0; i < col; i++) {
            newRow += ",";
        }
        newRow += data;

        rows.push_back(newRow);
    }

    // Write the updated rows to the file
    std::ofstream outputFile(filename);
    for (const auto& row : rows) {
        outputFile << row << std::endl;
    }
    outputFile.close();
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

std::string FileHandler::getConfigValue(const std::string& input) {
    std::ifstream configFile("configuration/config.txt");
    std::string line;
    std::regex regexInput(input + "\\s*=\\s*\\[(.*?)\\]");

    while (std::getline(configFile, line)) {
        std::smatch match;
        if (std::regex_search(line, match, regexInput)) {
            if (match.size() > 1) {
                return match[1].str();
            }
        }
    }
    return "";
}

/*std::string FileHandler::getConfigValue(const std::string& parameter) {
    std::ifstream configFile("configuration/config.txt");
    std::string line;
    std::string value;

    if (configFile.is_open()) {
        while (std::getline(configFile, line)) {
            // Find the line containing the parameter
            if (line.find(parameter) != std::string::npos) {
                // Extract the value within the square brackets
                size_t startPos = line.find('[');
                size_t endPos = line.find(']');
                if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
                    value = line.substr(startPos + 1, endPos - startPos - 1);
                }
                break;
            }
        }
        configFile.close();
    }

    return value;
}*/