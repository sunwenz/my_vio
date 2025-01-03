#include "my_vio.h"

Vio::Vio(const std::string& congfig_file){
    std::cout << "Vio::Vio()" << std::endl;
}

void Vio::addNewImage(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    num_of_image_++;;sasfW

    // step 1. preprofcess img
    if(img_left.channels() == 3){
        cv::cvtColor(img_left, img_left, cv::COLOR_BGR2GRAY);
    }

    if(!img_right.empty() && img_right.channels() == 3){
        cv::cvtColor(img_right, img_right, cv::COLOR_BGR2GRAY);
    }
    
    // step 2. create frame
    Frame::Ptr new_frame = Frame::createFrame(t, img_left, img_right);

    // step 3. frontend track image
    
}

