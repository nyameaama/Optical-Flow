#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

std::string getConfigValue(const std::string& input);

int main(){
    std::cout << getConfigValue("OUTPUT") << std::endl;
    return 0;
}

std::string getConfigValue(const std::string& input) {
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