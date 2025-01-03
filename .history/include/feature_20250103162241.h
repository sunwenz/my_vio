#include "common/commonInclude.h"

class Feature{
public:
    using Ptr = std::shared_ptr<Feature>;

    Feature(ulong id, const Vec3& pos, double depth)
        : id_(id), pos_(pos), depth_(depth), is_outlier_(false) {}

    ~Feature() {}

    static Feature::Ptr createFeature(ulong id, const Vec3& pos, double depth);

    void setOutlier(bool is_outlier){
        is_outlier_ = is_outlier;
    }

    bool isOutlier() const {
        return is_outlier_;
    }

    ulong id() const {
        return id_;
    }

    Vec3 pos() const {
        return pos_;
    }

    double depth() const {
        return depth_;
    }

    void setDepth(double depth){
        depth_ = depth;
    }

    void setPos(const Vec3& pos){
        pos_ = pos;
    }

private:
    ulong id_;
    Vec3 pos_;
    double depth_;

    bool is_outlier_;
};