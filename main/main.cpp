#include <iostream>
#include <string>
#include "_init.h"
#include "_analysis.h"
#include "_FileHandler.h"

int main(int argc, char* argv[]) {
    std::cout << "Optical Flow on In-Vitro Experimentations" << std::endl;
    auto *initObj = new _initialise();
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

    if (path.empty() || out.empty()) return 1;

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
    //Next Step
    cv::VideoCapture video(path);
    //auto *opticalFlowObj = new OpticalFlow(video, ROI_int_conversion);
    //opticalFlowObj -> processFrames(video);

    MouseKalmanFilter filter;
    filter.run();

    //Delete Objects
    delete initObj;
    delete fileHandlerObj;
    //delete opticalFlowObj;
}