#include "frame.h"

Frame::Frame(double t, const cv::Mat& img_left, const cv::Mat& img_right)
    : timestamp_(t), img_left_(img_left), img_right_(img_right) 
{
    rows_ = img_left.rows;
    cols_ = img_left.cols;
}

Frame::~Frame() {}

Frame::Ptr Frame::createFrame(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    return std::make_shared<Frame>(t, img_left, img_right);
}