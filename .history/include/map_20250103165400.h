#pragma once

#include "common/commonInclude.h"

class Map{
public:
    using Ptr = std::shared_ptr<Map>;
    
    Map() = default;

    Map(size_t size_of_sliding_window);

    size_t sizeOfSlidingWindow() const;

    ~Map();

private:
    size_t size_of_sliding_window_ = 10;
    std::mutex map_mutex_;

    std::unordered_map<ulong, Feature::Ptr> features_;
    std::queue<Frame::Ptr> keyframes_;

};