#include "my_vio.h"

Vio::Vio(const std::string& congfig_file){
    std::cout << "Vio::Vio()" << std::endl;
}

Vio::addNewImage(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    num_of_image_++;

    // step 1. frontend add new frame

    // step 2. 
}