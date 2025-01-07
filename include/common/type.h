#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>
using MatXX = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;

#include <sophus/se3.hpp>
#include <sophus/so3.hpp>
using SE3 = Sophus::SE3d;
using SO3 = Sophus::SO3d;

struct GNSS
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    
    double timestamp_;
    Eigen::Vector3d blh_;
    Eigen::Vector3d std_;
};

struct Imu
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    using Ptr = std::shared_ptr<Imu>;

    Imu() = default;
    Imu(double t, const Eigen::Vector3d& gyro, const Eigen::Vector3d& accel) 
        : timestamp_(t), gyro_(gyro), accel_(accel) {}

    double timestamp_;
    Eigen::Vector3d gyro_; // rad/s
    Eigen::Vector3d accel_;    // m/s^2
};


struct NavState {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    NavState() = default;

    // from time, R, p, v, bg, ba
    explicit NavState(double time, const SO3& R = SO3(), const Eigen::Vector3d& t = Eigen::Vector3d::Zero(), const Eigen::Vector3d& v = Eigen::Vector3d::Zero(),
                      const Eigen::Vector3d& bg = Eigen::Vector3d::Zero(), const Eigen::Vector3d& ba = Eigen::Vector3d::Zero())
        : timestamp_(time), R_(R), p_(t), v_(v), bg_(bg), ba_(ba) {}

    // from pose and vel
    NavState(double time, const SE3& pose, const Eigen::Vector3d& vel = Eigen::Vector3d::Zero())
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
    Eigen::Vector3d p_ = Eigen::Vector3d::Zero();   // 平移
    Eigen::Vector3d v_ = Eigen::Vector3d::Zero();   // 速度
    Eigen::Vector3d bg_ = Eigen::Vector3d::Zero();  // gyro 零偏
    Eigen::Vector3d ba_ = Eigen::Vector3d::Zero();  // acce 零偏
};

