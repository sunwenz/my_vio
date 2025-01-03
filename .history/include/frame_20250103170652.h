#pragma once

#include "common/commonInclude.h"

class Frame{
public:
    using Ptr = std::shared_ptr<Frame>;

    
    
    ~Frame();

private:
    ulong id_;
    ulong keyframe_id_;
    
    SE3 pose_;


};