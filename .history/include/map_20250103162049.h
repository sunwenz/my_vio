#pragma once

#include "common/commonInclude.h"

class Map{
public:
    using Ptr = std::shared_ptr<Map>;
    
    Map();

    ~Map();

private:
    std::unordered_map<ulong, Feature::Ptr> features_;
    std::queue<Frame::Ptr> keyframes_;
    
};