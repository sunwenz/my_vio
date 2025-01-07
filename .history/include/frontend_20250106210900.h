#pragma once

#include "common/commonInclude.h"
#include "frame.h"

class Frontend{ // 前端     
public:
    using Ptr = std::shared_ptr<Frontend>;
    
    static constexpr int MAX_FEATURES = 10.0;

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
private:
    double timestamp_;
    
    bool initialized_{false};

    Camear::Ptr camera_{nullptr};
    Frame::Ptr current_frame_{nullptr};
    Frame::Ptr last_frame_{nullptr};

    std::vector<cv::Point2f> keypoints_curr_;
    std::vector<cv::Point2f> keypoints_last_;

    cv::Mat mask_;
};