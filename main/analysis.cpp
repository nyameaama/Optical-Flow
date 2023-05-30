#include"analysis.h"

void _Analysis::analysisStep1(const std::string& filename){
    //Define Video File to OpenCV
    cv::VideoCapture cap(filename);
    //Initialise openCV variables
    cv::Mat previousFrame, currentFrame;
    //Define Previous Frame variable as video data
    cap >> previousFrame;
    //Convert frame to grayscale
    cv::cvtColor(previousFrame, previousFrame, cv::COLOR_BGR2GRAY);
    //Get Region of Interest and define it in openCV 
    cv::Rect roi(100, 100, 200, 200);

    cv::Mat prevRoi = prevFrame(roi);
}