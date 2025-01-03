#include "common/commonInclude.h"

class Feature{
public:
    using Ptr = std::shared_ptr<Feature>;

    Feature(ulong id, const Vec3& pos, double depth)
        : id_(id), pos_(pos), depth_(depth), is_outlier_(false) {}

    ~Feature() {}

    static Feature::Ptr createFeature(ulong id, const Vec3& pos, double depth);

    Vec3 getPos() const {
        return pos_;
    }

    double getDepth() const {
        return depth_;
    }

    void setDepth(double depth){
        depth_ = depth;
    }

    ulong getId() const {
        return id_;
    }

    bool isOutlier() const {
        return is_outlier_;
    }

    void setOutlier(bool is_outlier){
        is_outlier_ = is_outlier;
    }
private:
    ulong id_;
    Vec3 pos_;
    double depth_;

    bool is_outlier_;
};