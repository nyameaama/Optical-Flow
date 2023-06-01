#include "_init.h"

//Read Region of Interest Coordinates from Configuration File
std::string _initialise::readROIFromConfig(){
    auto *object = new FileHandler();
    std::string parameter = "ROI";
    std::string value = object -> getConfigValue(parameter);
    if (value.empty()) {
        std::cerr << "Parameter '" << parameter << "' not found in the config file.\n";
        return "";
    }
    delete object;
    return value;
}

//Read File Path from Configuration File
std::string _initialise::readFilePathFromConfig(){
    auto *object = new FileHandler();
    std::string parameter = "PATH";
    std::string value = object -> getConfigValue(parameter);
    if (value.empty()) {
        std::cerr << "Parameter '" << parameter << "' not found in the config file.\n";
        return "";
    }
    delete object;
    return value;
}

//Read File Path from Configuration File
std::string _initialise::readOutputPathFromConfig(){
    auto *object = new FileHandler();
    std::string parameter = "OUTPUT";
    std::string value = object -> getConfigValue(parameter);
    if (value.empty()) {
        std::cerr << "Parameter '" << parameter << "' not found in the config file.\n";
        return "";
    }
    delete object;
    return value;
}

//Check to see if host machine has OpenCV and all related dependencies
bool _initialise::dependencyCheck(){
    try {
        //checking for the 'OpenCV' library, you can try to include an OpenCV header file
        #include <opencv2/core/core.hpp>

        // If the library is installed, this code block will be executed
        std::cout << "Initial Check: ";
        std::clog << "Library is installed.\n";
        return true;
    }
    catch (...) {
        // If an exception is thrown, this code block will be executed
        // Here, you can choose to handle the exception silently without displaying an error message
        std::cerr << "OpenCV is not installed.\n";
        return false;
    }
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
        std::cerr << "Failed to open video: " << filename << '\n';
        return false;
    }
    return true;
}

bool _initialise::isImageReadable(const std::string& filename) {
    cv::Mat image = cv::imread(filename);
    if (image.empty()) {
        std::cerr << "Failed to open image: " << filename << '\n';
        return false;
    }
    return true;
}

bool _initialise::isVideoFile(const std::string& filepath) {
    cv::VideoCapture capture(filepath);
    if (!capture.isOpened()) {
        std::cerr << "Failed to open file: " << filepath << '\n';
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

std::vector<int> _initialise::convertStringToIntArray(const std::string& values) {
    std::stringstream ss(values);
    std::vector<int> intArray;
    int value;

    while (ss >> value) {
        intArray.push_back(value);
        if (ss.peek() == ',')
            ss.ignore();
    }

    return intArray;
}