#ifndef INITIALISE
#define INITIALISE

#include<iostream>
#include"_FileHandler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include <string>
#include <vector>

struct VideoProperties {
    int numFrames;
    double fps;
    int width;
    int height;
};

class _initialise {
    public:
        //Read Region of Interest Coordinates from Configuration File
        std::string readROIFromConfig();

        //Read File Path from Configuration File
        std::string readFilePathFromConfig();

        //Read File Path from Configuration File
        std::string readOutputPathFromConfig();

        //Check to see if host machine has OpenCV and all related dependencies
        bool dependencyCheck();

        //Check to see if content is valid 
        bool contentCheck(const std::string& filename);

        VideoProperties getVideoProperties(const std::string& filepath);

        std::vector<int> convertStringToIntArray(const std::string& values);

    private:
        bool isVideoReadable(const std::string& filename);

        bool isImageReadable(const std::string& filename);

        bool isVideoFile(const std::string& filepath);

};


#endif //INITIALISE