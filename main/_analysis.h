#ifndef MOUSE_KALMAN_H
#define MOUSE_KALMAN_H

#include "opencv2/video/tracking.hpp"
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "_init.h"

#define drawCross(center, color, d) \
    line(display_image, Point(center.x - d, center.y - d), Point(center.x + d, center.y + d), color, 2, LINE_AA, 0); \
    line(display_image, Point(center.x + d, center.y - d), Point(center.x - d, center.y + d), color, 2, LINE_AA, 0)

void on_mouse(int e, int x, int y, int d, void *ptr);

class MouseKalmanFilter {
public:
    void run();
    void drawRectangle(cv::Mat& image, const cv::Point& center, int size, const cv::Scalar& color);
    cv::Point convertROIToXY(int roiX, int roiY, int roiWidth, int roiHeight);
private:
    cv::KalmanFilter KF;
    cv::Mat display_image;
    double ticks;
    cv::Point mousePos;
};

#endif