#ifndef INITIALISE
#define INITIALISE

#include<iostream>
#include"_FileHandler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
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
        std::string readROIfromConfig();

        //Read File Path from Configuration File
        std::string readfilePathfromConfig();


        uint8_t readFrameLimit();

        //Check to see if host machine has OpenCV and all related dependencies
        bool dependencyCheck();

        //Check to see if content is valid 
        bool contentCheck(const std::string& filename);

        VideoProperties getVideoProperties(const std::string& filepath);

    private:
        bool isVideoReadable(const std::string& filename);

        bool isImageReadable(const std::string& filename);

        bool isVideoFile(const std::string& filepath);

};


#endif //INITIALISE