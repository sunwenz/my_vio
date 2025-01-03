#include "common/commonInclude.h"

class Feature{
public:
    using Ptr = std::shared_ptr<Feature>;

    Feature(ulong id, const Vec3& pos, double depth)
        : id_(id), pos_(pos), depth_(depth), is_outlier_(false) {}

    ~Feature() {}

    static Feature::Ptr createFeature(ulong id, const Vec3& pos, double depth);

private:
    ulong id_;
    Vec3 pos_;
    double depth_;

    bool is_outlier_;
};