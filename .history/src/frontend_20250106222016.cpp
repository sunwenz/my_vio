#include "frontend.h"

Status Frontend::trackFrame(Frame::Ptr frame){
    Status track_status = OK;
    
    if(!initialized_){
        // step 1. init frontend
        initialized_ = true;
        featuresDetection(frame);
        current_frame_ = frame;
        return track_status;
    }

    keypoints_curr_.clear();

    // step 2. track image by lk ans reverse check
    std::vector<uchar> status;
    std::vector<float> err;
    cv::calcOpticalFlowPyrLK(last_frame_->imgLeft(), current_frame_->imgLeft(), keypoints_last_, keypoints_curr_, status, err);

    // step 3. reverse check
    std::vector<cv::Point2f> keypoints_last_reverse;
    std::vector<uchar> status_reverse;
    std::vector<float> err_reverse;
    cv::calcOpticalFlowPyrLK(current_frame_->imgLeft(),
                             last_frame_->imgLeft(),
                             keypoints_curr_, 
                             keypoints_last_reverse,
                            status_reverse, err_reverse);
    
    for(size_t i = 0; i < status.size(); i++){
        if(status[i] && status_reverse[i] && calPixelDistance(keypoints_last_[i], keypoints_last_reverse[i]) < 1.0 && inBorder(keypoints_curr_[i])){
            status[i] = 1;
        }else{
            status[i] = 0;
        }
    }
    
    // step 4. remove outlier
    reduceVector(keypoints_curr_, status);
    reduceVector(keypoints_last_, status);

    setMask();
    
    {
        Timer timer;
        const int n_max_cnt = MAX_FEATURES - static_cast<int>(keypoints_curr_.size());
        if(n_max_cnt > 0){
            if(mask_.empty()) {LOG(INFO) << "mask is empty";}
            if(mask_.type() != CV_8UC1) {LOG(INFO) << "mask type is not CV_8UC1";}

            featureDetection(frame);
        }else
            keypoints_new_.clear();

        for(const auto &p : keypoints_new_){
            keypoints_curr_.push_back(p);
        }
        LOG(INFO) << "NEW FEATURES: " << keypoints_new_.size() << ", TOOK " << timer.toc() << " ms.";
    }

    // track from left to right
    keypoints_curr_right_.clear();
    std::vector<uchar> status_l2r, status_r2l;
    std::vector<float> err;
    cv::calcOpticalFlowPyrLK(current_frame_->imgRight(), current_frame_->imgLeft(), keypoints_curr_, keypoints_curr_right_, status_right, err_right);


    
    return track_status;
}

bool Frontend::preprofcessImgTwo(Frame::Ptr frame){

}

bool Frontend::preprofcessImg(Frame::Ptr frame){
    
}

double Frontend::calPixelDistance(const cv::Point2f& p1, const cv::Point2f& p2){
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void Frontend::featureDetection(Frame::Ptr frame){
    cv::goodFeaturesToTrack(frame->imgLeft(), keypoints_new_, MAX_FEATURES, 0.01, MIN_DIST, mask_);
}

void Frontend::setMask(){
    mask_ = cv::Mat(camera_->height(), camera_->width(), CV_8UC1, cv::Scalar(255));
    for(const auto &p : keypoints_curr_){
        cv::circle(mask_, p, 10, 0, -1);
    }
}

template <typename T> void Frontend::reduceVector(T &vec, vector<uchar> status) {
    size_t index = 0;
    for (size_t k = 0; k < vec.size(); k++) {
        if (status[k]) {
            vec[index++] = vec[k];
        }
    }
    vec.resize(index);
}

bool Frontend::inBorder(const cv::Point2f &pt) {
    const int border = 1;
    int x = cvRound(pt.x);
    int y = cvRound(pt.y);
    return border <= x && x < camera_->width() - border && border <= y && y < camera_->height() - border;
}