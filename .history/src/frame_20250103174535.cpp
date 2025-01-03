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