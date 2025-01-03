#include "frame.h"

Frame::Frame(ulong id, double t, const cv::Mat& img_left, const cv::Mat& img_right)
    : id_(id), timestamp_(t), img_left_(img_left), img_right_(img_right){}

Frame::Ptr Frame::createFrame(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    static ulong factory_id = 0;
    return std::make_shared<Frame>(factory_id++, t, img_left, img_right);
}

Frame::~Frame() {}

Frame::Ptr Frame::createFrame(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    return std::make_shared<Frame>(t, img_left, img_right);
}

ulong Frame::id() const{
    return id_;
}

double Frame::timestamp() const{
    return timestamp_;
}

coonst cv::Mat& Frame::imgLeft() const{
    return img_left_;
}

const cv::Mat& Frame::imgRight() const{
    return img_right_;
}

SE3 Frame::pose() const{
    return pose_;
}

void Frame::setPose(const SE3& pose){
    pose_ = pose;
}

void Frame::setKeyframe(bool is_keyframe){
    is_keyframe_ = is_keyframe;
}

bool Frame::isKeyframe() const{
    return is_keyframe_;
}

void Frame::setKeyframeId(ulong keyframe_id){
    keyframe_id_ = keyframe_id;
}

void Frame::addFeature(ulong feature_id, const cv::Point2f& pixel_pos_left, const cv::Point2f& pixel_pos_right){
    features_[feature_id] = std::make_pair(pixel_pos_left, pixel_pos_right);
}

std::unordered_map<ulong, std::pair<cv::Point2f, cv::Point2f>> Frame::features() const{
    return features_;
}

ulong Frame::keyframeId() const{
    return keyframe_id_;
}
