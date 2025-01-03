#pragma once

#include "common/commonInclude.h"
#include "frame.h"

class Frontend{ // 前端     
public:
    using Ptr = std::shared_ptr<Frontend>;
    
    Frame::Ptr addNewFrame(double t, const cv::Mat& img_left, const cv::Mat& img_right = cv::Mat());
    
    Frontend();

private:
    
};