#include "OpticalFlowCalc.h"

OpticalFlow::OpticalFlow(cv::VideoCapture &videoCapture, std::vector<int>& vector_param) {
    videoCapture >> OpticalFlow::prevFrame;
    // Convert frame to grayscale
    cv::cvtColor(OpticalFlow::prevFrame, OpticalFlow::prevFrame, cv::COLOR_BGR2GRAY);
    // Get Region of Interest and define it in OpenCV
    cv::Rect roi(vector_param[0], vector_param[1], vector_param[2], vector_param[3]);

    OpticalFlow::ROI_Rect = roi;
    OpticalFlow::video = videoCapture;
    OpticalFlow::prevROI = OpticalFlow::prevFrame(roi);
}

void OpticalFlow::runOpticalFlow() {
    while (true) {
        OpticalFlow::video >> OpticalFlow::currFrame;
        if (OpticalFlow::currFrame.empty()) break;

        cv::Mat flow = OpticalFlow::calculateOpticalFlow();
        OpticalFlow::updateROI(flow);
        OpticalFlow::visualizeOpticalFlow(flow);

        OpticalFlow::prevFrame = OpticalFlow::currFrame;
    }
}

cv::Mat OpticalFlow::calculateOpticalFlow() {
    cv::Mat flow, prevGrey, currGrey;
    cv::cvtColor(OpticalFlow::prevFrame, OpticalFlow::prevFrame, cv::COLOR_BGR2GRAY);
    cv::cvtColor(OpticalFlow::currFrame, OpticalFlow::currFrame, cv::COLOR_BGR2GRAY);

    prevGrey = OpticalFlow::prevFrame(OpticalFlow::prevROI);
    currGrey = OpticalFlow::currFrame(OpticalFlow::prevROI);

    // Calculate optical flow
    calcOpticalFlowFarneback(prevGrey, currGrey, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    return flow;
}

void OpticalFlow::updateROI(cv::Mat& flow) {
    cv::Scalar mean_flow = cv::mean(flow); //Takes the average velocity of the flow

    //Updates the ROI accordingly
    OpticalFlow::ROI_Rect.x += mean_flow[0];
    OpticalFlow::ROI_Rect.y += mean_flow[1];

    //sets the previous ROI to the current ROI
    OpticalFlow::prevROI = OpticalFlow::prevFrame(OpticalFlow::ROI_Rect);
}

cv::Mat OpticalFlow::visualizeOpticalFlow(cv::Mat& flow) {
    cv::Mat cFlow;
    cvtColor(OpticalFlow::prevFrame, cFlow, cv::COLOR_GRAY2BGR);
    drawOpticalFlow(flow, cFlow, 16);
    return cFlow;
}

void OpticalFlow::drawOpticalFlow(const cv::Mat& flowMat, cv::Mat& cFlowMap, int step){
    for(int y = 0; y < cFlowMap.rows; y += step){
        for(int x = 0; x < cFlowMap.cols; x += step){
            const auto& fxy = flowMat.at<cv::Point2f>(y, x);
            line(cFlowMap, cv::Point(x, y), cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)),
                 CV_RGB(0, 255, 0));
            circle(cFlowMap, cv::Point(x, y), 2, CV_RGB(255, 0, 0), -1);
        }
    }
}