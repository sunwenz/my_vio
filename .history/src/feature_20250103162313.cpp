#include "feature.h"

Feature::Ptr Feature::createFeature(ulong id, const Vec3& pos, double depth){
    return std::make_shared<Feature>(id, pos, depth);
}

void Feature::setOutlier(bool is_outlier){
    is_outlier_ = is_outlier;
}