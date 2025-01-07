#pragma once

#include "common/commonInclude.h"
#include "frame.h"

class Frontend{ // 前端     
public:
    using Ptr = std::shared_ptr<Frontend>;
    
    static constexpr int MAX_FEATURES = 200.0;
    static constexpr int MIN_FEATURES = 30.0;

    enum Status{
        INIT = 1,
        OK = 2,
        LOST = 0
    };

    Frontend() = default;

    Status trackFrame(Frame::Ptr frame);
    
    bool preprofcessImgTwo(Frame::Ptr frame);
    bool preprofcessImg(Frame::Ptr frame);

    double calPixelDistance(const cv::Point2f& p1, const cv::Point2f& p2);

private:
    template <typename T> void reduceVector(T &vec, vector<uchar> status);

    void featureDetection(Frame::Ptr frame);

    void setMask();
private:
    double timestamp_;
    
    bool initialized_{false};

    Camear::Ptr camera_{nullptr};
    Frame::Ptr current_frame_{nullptr};
    Frame::Ptr last_frame_{nullptr};

    std::vector<cv::Point2f> keypoints_curr_, keypoints_curr_right_;
    std::vector<cv::Point2f> keypoints_last_;
    std::vector<cv::Point2f> keypoints_new_;

    cv::Mat mask_ = cv::Mat(camera_->height(), camera_->width(), CV_8UC1, cv::Scalar(255));
};