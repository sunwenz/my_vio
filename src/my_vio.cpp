#include "my_vio.h"

Vio::Vio(const std::string& congfig_file){
    std::cout << "Vio::Vio()" << std::endl;
}

void Vio::addNewImage(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    num_of_image_++;
    
    // step 2. create frame
    Frame::Ptr new_frame = Frame::createFrame(t, img_left, img_right);

    // step 3. frontend track image
    int status = frontend_->trackImage(new_frame);

    
}




