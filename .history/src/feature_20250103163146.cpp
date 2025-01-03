#include "feature.h"

Feature::Feature(ulong id, const Vec3& pos, double depth)
    : id_(id), pos_(pos), depth_(depth), is_outlier_(false)
{}

Feature::Ptr Feature::createFeature(ulong id, const Vec3& pos, double depth){
    static ulong factory_id = 0;
    return std::make_shared<Feature>(factory_id++, pos, depth);
}

void Feature::setOutlier(bool is_outlier){
    is_outlier_ = is_outlier;
}

bool Feature::isOutlier() const{
    return is_outlier_;
}

ulong Feature::id() const{
    return id_;
}

Vec3 Feature::pos() const{
    return pos_;
}

double Feature::depth() const{
    return depth_;
}

void Feature::setDepth(double depth){
    depth_ = depth;
}

void Feature::setPos(const Vec3& pos){
    pos_ = pos;
}



