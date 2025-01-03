#pragma once

#include "common/commonInclude.h"
#include "common/type.h"
#include "frontend.h"
#include "map.h"

class Vio{
public:
    Vio(const std::string& config_file);

    void addNewImu(const Imu& imu_data);
private:
    Frontend::Ptr frontend_;   
    
    Map::Ptr map_;    
};