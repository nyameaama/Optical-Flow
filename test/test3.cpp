#include "opencv2/video/tracking.hpp"
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define drawCross(center, color, d)                                                              \
    line(display_image, Point(center.x - d, center.y - d), Point(center.x + d, center.y + d),   \
         color, 2, LINE_AA, 0);                                                                  \
    line(display_image, Point(center.x + d, center.y - d), Point(center.x - d, center.y + d),   \
         color, 2, LINE_AA, 0)

using namespace cv;
using namespace std;

void drawRectangle(cv::Mat& image, const cv::Point& center, int size, const cv::Scalar& color) {
    int halfSize = size / 2;
    cv::Rect rect(center.x - halfSize, center.y - halfSize, size, size);
    cv::rectangle(image, rect, color, 2);
}


void on_mouse(int e, int x, int y, int d, void *ptr) {
    Point *p = (Point *)ptr;
    p->x = x;
    p->y = y;
}

int main() {
    // >>> Kalman Filter Initialization
    int stateSize = 4;  // [x, y, v_x, v_y]
    int measSize = 2;   // [z_x, z_y] // we will only measure mouse cursor x and y
    int contrSize = 0;  // no control input

    unsigned int F_type = CV_32F;

    // initiation of OpenCV Kalman Filter
    cv::KalmanFilter KF(stateSize, measSize, contrSize, F_type);

    // creating state vector
    cv::Mat state(stateSize, 1, F_type);  // [x, y, v_x, v_y] // column Matrix

    // creating measurement vector
    cv::Mat meas(measSize, 1, F_type);    // [z_x, z_y] // column matrix

    // Transition state matrix A
    // Note: set dT at each processing step!
    // X_k = A*X_k-1
    // X_k = current state := x_k, y_k, v_x_k
    // X_k-1 = previous state
    // A =
    // [1 0 dT 0]
    // [0 1 0 dT]
    // [0 0 1  0]
    // [0 0 0  1]
    // observe it is an identity matrix with dT inputs that we will provide later
    cv::setIdentity(KF.transitionMatrix);

    // Measurement Matrix (This is C or H matrix)
    // size of C is measSize x stateSize
    // only those values will set which we can get as measurement in a state vector
    // here out of [x, y, v_x and v_y] we can only measure x, y of the mouse cursor coordianates
    // so we set only element "0" and "5".
    // [1 0 0 0]
    // [0 1 0 0]

    KF.measurementMatrix = cv::Mat::zeros(measSize, stateSize, F_type);
    KF.measurementMatrix.at<float>(0) = 1.0f;
    KF.measurementMatrix.at<float>(5) = 1.0f;

    // Process Noise Covariance Matrix := stateSize x stateSize
    //  [Ex 0  0    0]
    //  [0 Ey  0    0]
    //  [0 0 E_v_x  0]
    //  [0 0  0  E_v_y]

    KF.processNoiseCov.at<float>(0) = 1e-2;
    KF.processNoiseCov.at<float>(5) = 1e-2;
    KF.processNoiseCov.at<float>(10) = 5.0f;
    KF.processNoiseCov.at<float>(15) = 5.0f;

    // Measure Noise Covariance Matrix
    cv::setIdentity(KF.measurementNoiseCov, cv::Scalar(1e-1));

    // <<< Kalman Filter initialization

    cv::VideoCapture video("../main/ExperimentalData/C0032.MP4");
    if (!video.isOpened()) {
        std::cout << "Could not open the video file." << std::endl;
        return -1;
    }

    cv::Mat display_image(600, 800, CV_8UC3);
    namedWindow("Video Tracking with Kalman Filter");

    char ch = 0;
    double ticks = 0;
    Point mousePos;
    while (ch != 'q' && ch != 'Q') {
        double precTick = ticks;
        ticks = (double)cv::getTickCount();

        double dT = (ticks - precTick) / cv::getTickFrequency(); // seconds

        // >>> Kalman Prediction
        // >>> Matrix A
        KF.transitionMatrix.at<float>(2) = dT;
        KF.transitionMatrix.at<float>(7) = dT;
        // <<< Matrix A

        std::cout << "dt: " << dT << std::endl;

        state = KF.predict(); // First predict, to update the internal statePre variable
        std::cout << "State post: " << state << std::endl;

        Point predictPt(state.at<float>(0), state.at<float>(1));
        // <<< Kalman Prediction

        // Read the next frame from the video
        cv::Mat frame;
        video >> frame;

        // If the frame is empty, end the loop
        if (frame.empty())
            break;

        // Define the ROI coordinates
        cv::Rect roi(900,500,100,100); // Adjust the values according to your desired ROI
        
        cv::Point objectPt(900, 550); // Example object coordinates (replace with your actual coordinates)

        // Draw green rectangle around the object
        cv::Rect rect(objectPt, cv::Size(200, 150)); // Example rectangle size (replace with your desired size)
        cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2); // Green rectangle (BGR color format), thickness = 2

        // Extract the ROI from the frame
        cv::Mat roiImage = frame(roi).clone();

        // Convert the ROI image to grayscale and perform preprocessing (if needed)
        cv::Mat grayImage;
        cv::cvtColor(roiImage, grayImage, cv::COLOR_BGR2GRAY);

        // Update the measurement vector with the tracking point from the ROI
        meas.at<float>(0) = predictPt.x;
        meas.at<float>(1) = predictPt.y;

         // >>> Kalman Update Phase
        Mat estimated = KF.correct(meas);

        Point statePt(estimated.at<float>(0), estimated.at<float>(1));
        Point measPt(meas.at<float>(0), meas.at<float>(1));

        // Visualization and drawing

        // Display the frame with the ROI and tracking results
        cv::imshow("Video Tracking with Kalman Filter", frame);

        // Draw rectangles around statePt and measPt
        drawRectangle(frame, statePt, 10, cv::Scalar(255, 255, 255)); // White rectangle
        drawRectangle(frame, measPt, 10, cv::Scalar(0, 0, 255));     // Red rectangle


        // Process keyboard input
        ch = cv::waitKey(10);
    }

    return 0;
}