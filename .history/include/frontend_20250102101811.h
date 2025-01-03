#pragma once

#include "common/commonInclude.h"
#include "frame.h"

class Frontend{ // 前端     
public:
    using Ptr = std::shared_ptr<Frontend>;
    
    Frame::Ptr trackImage(double t, const cv::Mat& img_left, const cv::Mat& img_right = cv::Mat());

    Frontend();

private:
    double timestamp_;
    cv::Mat img_left_, img_right_;
    cv::Mat img_left_pre_, img_right_pre_;
    size_t rows_, cols_;

    
};