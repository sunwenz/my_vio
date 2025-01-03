#include "frontend.h"

Fronted::Frontend(){}

Frame::Ptr Fronted::trackImage(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    timestamp_ = t;
    img_left_ = img_left;
    img_right_ = img_right;
    rows_ = img_left.rows;
    cols_ = img_left.cols;


    return nullptr;
}