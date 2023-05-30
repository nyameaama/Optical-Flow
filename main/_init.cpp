#include "_init.h"

//Read Region of Interest Coordinates from Configuration File
std::string _initialise::readROIfromConfig(){
    FileHandler *object = new FileHandler();
    std::string parameter = "ROI";
    std::string value = object -> getConfigValue(parameter);
    if (value.empty()) {
        std::cout << "Parameter '" << parameter << "' not found in the config file." << std::endl;
        return "";
    } 
    delete object;
    return value;
}

//Read File Path from Configuration File
std::string readfilePathfromConfig(){
    FileHandler *object = new FileHandler();
    std::string parameter = "PATH";
    std::string value = getConfigValue(parameter);
     if (value.empty()) {
        std::cout << "Parameter '" << parameter << "' not found in the config file." << std::endl;
        return "";
    } 
    delete object;
    return value;
}

uint8_t _initialise::readFrameLimit(){

}

//Check to see if host machine has OpenCV and all related dependencies
bool _initialise::dependencyCheck(){
    try {
        //checking for the 'OpenCV' library, you can try to include an OpenCV header file
        #include <opencv2/core/core.hpp>

        // If the library is installed, this code block will be executed
        std::cout << "Library is installed." << std::endl;
        return true;
    }
    catch (...) {
        // If an exception is thrown, this code block will be executed
        // Here, you can choose to handle the exception silently without displaying an error message
        std::cout << "OpenCV is not installed." << std::endl;
        return false;
    }
    return true;
}

//Check to see if content is valid 
bool _initialise::contentCheck(const std::string& filename){
    if(isVideoFile(filename)){
        bool isVideoValid = isVideoReadable(filename);
        return true;
    }
    return false;
}

bool _initialise::isVideoReadable(const std::string& filename) {
    cv::VideoCapture capture(filename);
    if (!capture.isOpened()) {
        std::cout << "Failed to open video: " << filename << std::endl;
        return false;
    }
    return true;
}

bool _initialise::isImageReadable(const std::string& filename) {
    cv::Mat image = cv::imread(filename);
    if (image.empty()) {
        std::cout << "Failed to open image: " << filename << std::endl;
        return false;
    }
    return true;
}

bool _initialise::isVideoFile(const std::string& filepath) {
    cv::VideoCapture capture(filepath);
    if (!capture.isOpened()) {
        std::cout << "Failed to open file: " << filepath << std::endl;
        return false;
    }
    return true;
}

VideoProperties _initialise::getVideoProperties(const std::string& filepath) {
    cv::VideoCapture capture(filepath);

    int numFrames = capture.get(cv::CAP_PROP_FRAME_COUNT);
    double fps = capture.get(cv::CAP_PROP_FPS);
    int width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);

    capture.release();

    return {numFrames, fps, width, height};
}
