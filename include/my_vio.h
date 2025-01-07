#pragma once

#include "common/commonInclude.h"
#include "common/type.h"
#include "frontend.h"
#include "map.h"
#include "frame.h"

class Vio{
public:
    Vio(const std::string& config_file);

    void addNewImu(const Imu& imu_data);

    void addNewImage(double t, const cv::Mat& img_left, const cv::Mat& img_right = cv::Mat());

private:
    Frontend::Ptr frontend_;   
    
    Map::Ptr map_;    

    std::queue<Imu> imu_buf_;

    size_t num_of_image_;
    std::queue<Frame::Ptr> img_buf_;

    std::mutex imu_buf_mutex_;
    std::mutex img_buf_mutex_;

    std::thread process_thread_;
    std::atomic<bool> process_flag_;
    
};