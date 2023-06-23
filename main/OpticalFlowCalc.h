/*#ifndef OPTICAL_FLOW_OPTICALFLOWCALC_H
#define OPTICAL_FLOW_OPTICALFLOWCALC_H

#include "opencv2/opencv.hpp"

class OpticalFlow {
    cv::VideoCapture video;
    cv::Mat prevROI;
    cv::Mat currFrame;
    cv::Mat prevFrame;
    cv::Rect ROI_Rect;

    void drawOpticalFlow(const cv::Mat& flowMat, cv::Mat& cFlowMap, int step);
    void updateROI(cv::Mat& flow);
    cv::Mat calculateOpticalFlow();
    cv::Mat visualizeOpticalFlow(cv::Mat& flow);

    public:
        OpticalFlow(cv::VideoCapture &videoCapture, std::vector<int>& vector_param);

        void runOpticalFlow();
};

#endif //OPTICAL_FLOW_OPTICALFLOWCALC_H
*/