#pragma once

#include "common/commonInclude.h"

class Vio{
public:
    Vio(const std::string& config_file);

    
private:
    Frontend::Ptr frontend_;   
    
    Map::Ptr map_;
};