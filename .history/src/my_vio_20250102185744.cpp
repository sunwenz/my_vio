#include "my_vio.h"

Vio::Vio(const std::string& congfig_file){
    std::cout << "Vio::Vio()" << std::endl;
}

Vio::addNewImage(double t, const cv::Mat& img_left, const cv::Mat& img_right){
    num_of_image_++;

    // step 1. preprofcess img
    if(img_left.channels() == 3){
        cv::cvtColor(img_left, img_left, cv::COLOR_BGR2GRAY);
    }

    if(!img_right.empty() && img_right.channels() == 3){
        cv::cvtColor(img_right, img_right, cv::COLOR_BGR2GRAY);
    }
    // step 2. create frame

    // step 3. frontend track image

}

