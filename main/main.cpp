#include <iostream>
#include <string>
#include "_init.h"
#include "analysis.h"

int main(int argc, char* argv[]) {
    auto *initObj = new _initialise();
    auto *analysisObj = new _Analysis();

    //Check if dependencies available
    bool dependencyAvailable = initObj -> dependencyCheck();
    if (!dependencyAvailable) {
        return 1;
    }

    //Get content path from config file
    std::string path = initObj -> readFilePathFromConfig();

    //Perform content check
    bool contentAvailable = initObj -> contentCheck(path);
    if (!contentAvailable) {
        std::cerr << "There is problem loading the experimental data\n";
        return 1;
    } else {
        //Push some video metadata to output csv

    }

    //Get Region of Interest from config file
    uint16_t regionOfInterest;

    //Start Performing analysis

    //Initial Step1
    analysisObj -> analysisStep1(path);


    delete initObj;
    delete analysisObj;
}