#ifndef _ANALYSIS_H
#define _ANALYSIS_H

#include <vector>
#include <opencv2/opencv.hpp>

class OpticalFlow {
public:
    OpticalFlow(cv::VideoCapture& videoCapture, std::vector<int>& roiParams);

    void processFrames(cv::VideoCapture& videoCapture);

private:
    cv::Mat prevFrame;
    std::vector<cv::Point2f> prevPoints;
    std::vector<cv::Point2f> currPoints;
    std::vector<uchar> status;
    std::vector<float> err;
    cv::Mat state;
    cv::Mat measurement;
    cv::KalmanFilter kalmanFilter;
    std::vector<int> roiParams;
};

#endif  // _ANALYSIS_H