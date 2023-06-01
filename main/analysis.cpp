#include"analysis.h"

std::tuple<cv::Mat, cv::Mat, cv::Mat> _Analysis::analysisStep1(const std::string& filename, std::vector<int>& vector_param) {
    // Define Video File to OpenCV
    cv::VideoCapture cap(filename);
    // Initialise OpenCV variables
    cv::Mat previousFrame, currentFrame;
    // Define Previous Frame variable as video data
    cap >> previousFrame;
    // Convert frame to grayscale
    cv::cvtColor(previousFrame, previousFrame, cv::COLOR_BGR2GRAY);
    // Get Region of Interest and define it in OpenCV 
    cv::Rect roi(vector_param[0], vector_param[1], vector_param[2], vector_param[3]);

    cv::Mat prevRoi = previousFrame(roi);

    return std::make_tuple(previousFrame, currentFrame, prevRoi);
}