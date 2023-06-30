#ifndef OPTICAL_FLOW_OPTICALFLOWCALC_H
#define OPTICAL_FLOW_OPTICALFLOWCALC_H

#include "opencv2/opencv.hpp"
#include <fstream>

class OpticalFlow {
    cv::VideoCapture video;
    cv::Mat prevROI;
    cv::Mat currFrame;
    cv::Mat prevFrame;
    cv::Rect ROI_Rect;

    void drawOpticalFlow(const cv::Mat& flowMat, cv::Mat& cFlowMap, int step);
    void updateROI(const cv::Mat& flow);
    cv::Mat calculateOpticalFlow();
    cv::Mat visualizeOpticalFlow(const cv::Mat& flow);
    void saveOpticalFlowMatrix(const cv::Mat& flow, const std::string& filename);

    public:
        OpticalFlow(cv::VideoCapture &videoCapture, std::vector<int>& vector_param);

        void runOpticalFlow();
};

#endif //OPTICAL_FLOW_OPTICALFLOWCALC_H
