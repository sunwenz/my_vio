#pragma once

#include "common/commonInclude.h"
#include "common/type.h"
#include "frontend.h"
#include "map.h"

class Vio{
public:
    Vio(const std::string& config_file);

    void addNewImu(const Imu& imu_data);

    void addNewImage(double t, const cv::Mat& img_left, const cv::Mat& img_right = cv::Mat());

    
private:
    Frontend::Ptr frontend_;   
    
    Map::Ptr map_;    
};