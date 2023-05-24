#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    // Check if OpenCV is installed and accessible
    if (CV_MAJOR_VERSION < 2) {
        std::cout << "OpenCV version is too old or not found." << std::endl;
        return 1;
    }
    std::cout << "OpenCV version is ";
    std::cout << CV_MAJOR_VERSION << std::endl;

    // Load and display an image
    cv::Mat image = cv::imread("/Users/nyameaama/Downloads/Optical-Flow-Featured.png");

    // Check if the image was loaded successfully
    if (image.empty()) {
        std::cout << "Failed to load the image." << std::endl;
        return 1;
    }

    // Create a window and display the image
    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    cv::imshow("Image", image);
    cv::waitKey(0);

    return 0;
}