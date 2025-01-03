#pragma once

#include "common/commonInclude.h"

class Frame{
public:
    using Ptr = std::shared_ptr<Frame>;

    static Frame::Ptr createFrame(double t, const cv::Mat& img_left, const cv::Mat& img_right);

    Frame(double t, const cv::Mat& img_left, const cv::Mat& img_right);
    
    ~Frame();

private:
    
};