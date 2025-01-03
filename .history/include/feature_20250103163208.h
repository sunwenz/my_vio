#include "common/commonInclude.h"

class Feature{
public:
    using Ptr = std::shared_ptr<Feature>;

    Feature(ulong id, const Vec3& pos, double depth);
    
    ~Feature() = default;

    static Feature::Ptr createFeature(ulong id, const Vec3& pos, double depth);

    void setOutlier(bool is_outlier);

    bool isOutlier() const;

    ulong id() const;

    Vec3 pos() const;

    double depth() const ;

    void setDepth(double depth);

    void setPos(const Vec3& pos);

private:
    ulong id_;
    Vec3 pos_;
    double depth_;

    bool is_outlier_;
};