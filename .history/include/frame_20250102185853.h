#pragma once

#include "common/commonInclude.h"

class Frame{
public:
    using Ptr = std::shared_ptr<Frame>;

    Frame(double t, const cv::Mat& img_left, const cv::Mat& img_right = cv::Mat());
    
    ~Frame();

private:
    
};