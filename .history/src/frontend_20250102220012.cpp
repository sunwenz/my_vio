#include "frontend.h"

Fronted::Frontend(){}

Frame::Ptr Fronted::trackImage(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    timestamp_ = t;
    img_left_ = img_left;
    img_right_ = img_right;
    rows_ = img_left.rows;
    cols_ = img_left.cols;

    cv::calcOpticalFlowPyrLK(img_left_pre_, img_left_, prev_pts_, cur_pts_, status_, err_);


    return nullptr;
}