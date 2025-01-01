#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <unordered_map>

using MatXX = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;

struct GNSSData {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    
    double timestamp_;
    Vec3 blh_;
    Vec3 std_;

    GNSSData enu(const Vec3 &origin){
        Vec3 temp = blh_;
        blh_[0] = temp[1];
        blh_[1] = temp[0];
        Mat33 Dr = DR(origin);

        return {timestamp_,
                global2local(origin,blh_),
                std_};
    }
};

struct ImuData
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    ImuData() = default;
    ImuData(double t, const Vec3& gyro, const Vec3& accel) 
        : timestamp_(t), gyro_(gyro), accel_(accel) {}

    double timestamp_;
    Vec3 gyro_; // rad/s
    Vec3 accel_;    // m/s^2
};


struct NavState {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    NavState() = default;

    // from time, R, p, v, bg, ba
    explicit NavState(double time, const SO3& R = SO3(), const Vec3& t = Vec3::Zero(), const Vec3& v = Vec3::Zero(),
                      const Vec3& bg = Vec3::Zero(), const Vec3& ba = Vec3::Zero())
        : timestamp_(time), R_(R), p_(t), v_(v), bg_(bg), ba_(ba) {}

    // from pose and vel
    NavState(double time, const SE3& pose, const Vec3& vel = Vec3::Zero())
        : timestamp_(time), R_(pose.so3()), p_(pose.translation()), v_(vel) {}

    /// 转换到Sophus
    SE3 getSE3() const { return SE3(R_, p_); }

    friend std::ostream& operator<<(std::ostream& os, const NavState& s) {
        os << "p: " << s.p_.transpose() << ", v: " << s.v_.transpose()
           << ", q: " << s.R_.unit_quaternion().coeffs().transpose() << ", bg: " << s.bg_.transpose()
           << ", ba: " << s.ba_.transpose();
        return os;
    }

    friend void writeNavStateToFile(const NavState& s, std::ofstream& ofs){
        if (ofs.is_open()) {
            ofs << s.timestamp_ << " "
                << s.p_.transpose() << " "
                << s.v_.transpose() << " "
                << DCM2Angles(s.R_.matrix()).transpose() * R2D << " "
                << s.bg_.transpose() << " "
                << s.ba_.transpose() << std::endl;
        }
    }

    friend void writeNavStateBlhToFile(NavState s, std::ofstream& ofs){
        if (ofs.is_open()) {
            s.p_[0] = s.p_[0] * R2D;
            s.p_[1] = s.p_[1] * R2D;
            ofs  << std::fixed << std::setprecision(10)
                << s.timestamp_ << " "
                << s.p_.transpose() << " "
                << s.v_.transpose() << " "
                << DCM2Angles(s.R_.matrix()).transpose() * R2D << " "
                << s.bg_.transpose() << " "
                << s.ba_.transpose() << std::endl;
        }
    }


    double timestamp_ = 0;    // 时间
    SO3 R_;                   // 旋转
    Vec3 p_ = Vec3::Zero();   // 平移
    Vec3 v_ = Vec3::Zero();   // 速度
    Vec3 bg_ = Vec3::Zero();  // gyro 零偏
    Vec3 ba_ = Vec3::Zero();  // acce 零偏
};

