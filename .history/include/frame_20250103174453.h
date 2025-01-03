#pragma once

#include "common/commonInclude.h"

class Frame{
public:
    using Ptr = std::shared_ptr<Frame>;

    Frame(ulong id, double t, const cv::Mat& img_left, const cv::Mat& img_right);

    static Frame::Ptr createFrame(double t, const cv::Mat& img_left, const cv::Mat& img_right);
    
    ~Frame();

private:
    ulong id_;
    ulong keyframe_id_;

    double timestamp_;
    
    cv::Mat img_left_, img_right_;
    SE3 pose_;

    std::unordered_map<ulong, std::pair<cv::Point2f, cv::Point2f>> features_;   // feature_id, pixel_pos_of_left_img, pixel_pos_of_right_img
};