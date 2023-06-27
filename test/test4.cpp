#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/video/tracking.hpp>

class FluidFlowTracker {
public:
    FluidFlowTracker(const std::string& videoPath, const cv::Rect& roiRect)
        : videoCapture(videoPath), roiRect(roiRect), frameCount(0), totalVelocity(0), avgVelocity(0) {}

    void runFlowTracking() {
        cv::Mat prevFrame, currFrame;
        cv::Mat prevGray, currGray;
        cv::Mat flow, flowMap;

        videoCapture >> prevFrame;
        cv::cvtColor(prevFrame, prevGray, cv::COLOR_BGR2GRAY);

        while (true) {
            videoCapture >> currFrame;
            if (currFrame.empty())
                break;

            cv::cvtColor(currFrame, currGray, cv::COLOR_BGR2GRAY);

            // Calculate optical flow using Lucas-Kanade method with a Kalman filter
            cv::calcOpticalFlowFarneback(prevGray(roiRect), currGray(roiRect), flow, 0.5, 3, 15, 3, 5, 1.2, 0);

            // Visualize flow lines
            flowMap = visualizeFlowLines(flow);

            // Calculate average velocity
            cv::Scalar meanFlow = cv::mean(flow);
            double velocity = std::sqrt(meanFlow[0] * meanFlow[0] + meanFlow[1] * meanFlow[1]);
            totalVelocity += velocity;
            avgVelocity = totalVelocity / static_cast<double>(++frameCount);

            // Display flow map and velocity information
            cv::imshow("Fluid Flow Tracking", flowMap);
            std::cout << "Average Velocity: " << avgVelocity << std::endl;

            if (cv::waitKey(1) == 27) // ESC key to exit
                break;

            prevGray = currGray.clone();
        }

        cv::destroyAllWindows();
    }

private:
    cv::VideoCapture videoCapture;
    cv::Rect roiRect;
    int frameCount;
    double totalVelocity;
    double avgVelocity;

    cv::Mat visualizeFlowLines(const cv::Mat& flow) {
        cv::Mat flowMap;
        cv::cvtColor(flow, flowMap, cv::COLOR_GRAY2BGR);

        for (int y = 0; y < flowMap.rows; y += 10) {
            for (int x = 0; x < flowMap.cols; x += 10) {
                const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
                cv::line(flowMap, cv::Point(x, y), cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)),
                         cv::Scalar(0, 255, 0));
                cv::circle(flowMap, cv::Point(x, y), 2, cv::Scalar(255, 0, 0), -1);
            }
        }

        return flowMap;
    }
};

int main() {
    std::string videoPath = "path/to/your/video.mp4";
    cv::Rect roiRect(100, 100, 200, 200);  // Example ROI coordinates [x, y, width, height]

    FluidFlowTracker tracker(videoPath, roiRect);
    tracker.runFlowTracking();

    return 0;
}