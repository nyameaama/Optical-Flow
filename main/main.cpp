#include <iostream>
#include <string>
#include "_init.h"
#include "analysis.h"
#include "_FileHandler.h"
#include "OpticalFlowCalc.h"

int main(int argc, char* argv[]) {
    std::cout << "Optical Flow on In-Vitro Experimentations" << std::endl;
    auto *initObj = new _initialise();
    auto *analysisObj = new _Analysis();
    auto *fileHandlerObj = new FileHandler();

    //Check if dependencies available
    bool dependencyAvailable = initObj -> dependencyCheck();
    if (!dependencyAvailable) {
        return 1;
    }

    //Get content path from config file
    std::string path = initObj -> readFilePathFromConfig();
    //Get output path from config file
    std::string out = initObj -> readOutputPathFromConfig();

    fileHandlerObj -> writeToCSV(out,1,1,"Optical Flow on In-Vitro Experimentations");
    
    std::cout << "Experimental File: ";
    std::cout << path << std::endl;
    //Perform content check
    bool contentAvailable = initObj -> contentCheck(path);
    if (!contentAvailable) {
        std::cerr << "There is problem loading the experimental data\n";
        return 1;
    } else {
        //Push some video metadata to output csv
        fileHandlerObj -> writeToCSV(out,5,1,"METADATA");
    }
    //Get Region of Interest from config file
    std::string regionOfInterest = initObj -> readROIFromConfig();
    std::vector<int> ROI_int_conversion = initObj -> convertStringToIntArray(regionOfInterest);
    //Start Performing analysis

    //Initial Step1
    std::tuple<cv::Mat, cv::Mat, cv::Mat> result = analysisObj -> analysisStep1(path, ROI_int_conversion);

    //Next Step
    cv::VideoCapture video(path);
    auto *opticalFlowObj = new OpticalFlow(video, ROI_int_conversion);
    opticalFlowObj -> runOpticalFlow();

    //Delete Objects
    delete initObj;
    delete analysisObj;
    delete fileHandlerObj;
    delete opticalFlowObj;
}