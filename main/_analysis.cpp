#include "_analysis.h"

OpticalFlow::OpticalFlow(cv::VideoCapture& videoCapture, std::vector<int>& roiParams)
    : roiParams(roiParams) {
    // Initialize previous frame
    cv::Mat frame;
    videoCapture.read(frame);
    cv::cvtColor(frame, prevFrame, cv::COLOR_BGR2GRAY);

    // Initialize points for optical flow
    cv::goodFeaturesToTrack(prevFrame, prevPoints, 200, 0.3, 7, cv::noArray(), 7, false, 0.04);

    // Initialize measurement and state matrices
    int stateSize = 6;  // (x, y, vx, vy, ax, ay)
    int measSize = 2;   // (x, y)
    int contrSize = 0;  // No control inputs
    state = cv::Mat(stateSize, 1, CV_32F);
    measurement = cv::Mat(measSize, 1, CV_32F);

    // Initialize Kalman filter
    kalmanFilter.init(stateSize, measSize, contrSize, CV_32F);

    // Set transition matrix (A)
    kalmanFilter.transitionMatrix = (cv::Mat_<float>(stateSize, stateSize) <<
                                     1, 0, 1, 0, 0.5, 0,
                                     0, 1, 0, 1, 0, 0.5,
                                     0, 0, 1, 0, 1, 0,
                                     0, 0, 0, 1, 0, 1,
                                     0, 0, 0, 0, 1, 0,
                                     0, 0, 0, 0, 0, 1);

    // Set measurement matrix (H)
    kalmanFilter.measurementMatrix = cv::Mat::eye(measSize, stateSize, CV_32F);

    // Set process noise covariance matrix (Q)
    cv::setIdentity(kalmanFilter.processNoiseCov, cv::Scalar::all(1e-4));

    // Set measurement noise covariance matrix (R)
    cv::setIdentity(kalmanFilter.measurementNoiseCov, cv::Scalar::all(1e-1));

    // Set the error covariance matrix (P)
    cv::setIdentity(kalmanFilter.errorCovPost, cv::Scalar::all(1));

    // Initialize current points and status vector
    currPoints = prevPoints;
    status.resize(prevPoints.size(), 1);
}

void OpticalFlow::processFrames(cv::VideoCapture& videoCapture) {
    cv::Mat frame, grayFrame;
    std::vector<cv::Point2f> nextPoints;

    while (videoCapture.read(frame)) {
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Calculate optical flow
        std::vector<uchar> status;
        std::vector<float> err;
        std::vector<cv::Point2f> nextPointsFloat;
        cv::calcOpticalFlowPyrLK(prevFrame, grayFrame, prevPoints, nextPointsFloat, status, err);

        // Filter out points with low status
        size_t i, k;
        for (i = k = 0; i < nextPointsFloat.size(); i++) {
            if (!status[i])
                continue;

            nextPoints.push_back(nextPointsFloat[i]);
            k++;
        }
        nextPoints.resize(k);

        // Update Kalman filter state
        if (nextPoints.size() >= 2) {
            // Set measurement matrix (y = [x, y])
            measurement.at<float>(0) = nextPoints[0].x;
            measurement.at<float>(1) = nextPoints[0].y;

            // Correct the state using the measurement
            cv::Mat estimated = kalmanFilter.correct(measurement);

            // Extract the corrected position
            float x = estimated.at<float>(0);
            float y = estimated.at<float>(1);

            // Draw a circle at the corrected position
            cv::circle(frame, cv::Point(x, y), 5, cv::Scalar(0, 255, 0), -1);
        }

        // Display the frame
        cv::imshow("Video", frame);
        if (cv::waitKey(1) == 'q')
            break;

        // Update the previous frame and points
        std::swap(prevFrame, grayFrame);
        prevPoints = nextPoints;
    }
}