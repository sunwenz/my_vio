#include "common/commonInclude.h"


class Frame;
class Feature{
public:
    using Ptr = std::shared_ptr<Feature>;

    static constexpr double INIT_DEPTH = 10.0;
    static constexpr double MIN_DEPTH = 1.0;
    static constexpr double MAX_DEPTH = 200.0;

    Feature(ulong id, const Vec3& pos, double depth);
    
    ~Feature() = default;

    static Feature::Ptr createFeature(ulong id, const Vec3& pos, double depth = INIT_DEPTH);

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

    std::vector<Frame::Ptr> observed_frames_;
};