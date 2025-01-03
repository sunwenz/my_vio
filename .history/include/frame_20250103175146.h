#pragma once

#include "common/commonInclude.h"
#include "feature.h"


class Frame{
public:
    using Ptr = std::shared_ptr<Frame>;

    Frame(ulong id, double t, const cv::Mat& img_left, const cv::Mat& img_right);

    static Frame::Ptr createFrame(double t, const cv::Mat& img_left, const cv::Mat& img_right);
    
    ~Frame();

    ulong id() const;

    double timestamp() const;

    const cv::Mat& imgLeft() const;
    const cv::Mat& imgRight() const;

    SE3 pose() const;

    void setPose(const SE3& pose);

    void setKeyframe(bool is_keyframe);

    bool isKeyframe() const;

    void setKeyframeId(ulong keyframe_id);

    void addFeature(ulong feature_id, const cv::Point2f& pixel_pos_left, const cv::Point2f& pixel_pos_right);

    std::unordered_map<ulong, std::pair<cv::Point2f, cv::Point2f>> features() const;

    ulong keyframeId() const;

private:
    ulong id_;
    ulong keyframe_id_;

    double timestamp_;
    
    cv::Mat img_left_, img_right_;
    SE3 pose_;

    bool is_keyframe_;

    std::unordered_map<ulong, std::pair<cv::Point2f, cv::Point2f>> features_;   // feature_id, pixel_pos_of_left_img, pixel_pos_of_right_img
};