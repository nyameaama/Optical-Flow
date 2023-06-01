#ifndef _ANALYSIS
#define _ANALYSIS

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

class _Analysis{
    public:
        std::tuple<cv::Mat, cv::Mat, cv::Mat> analysisStep1(const std::string& filename, std::vector<int>& vector_param);

};

#endif //_ANALYSIS