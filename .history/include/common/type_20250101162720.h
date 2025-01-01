#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <unordered_map>

using MatXX = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;

struct GnssData
{
    
};

struct ImuData
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    double timestamp;//GPS周内秒（s）
    Eigen::Vector3d gyro;//陀螺输出的角速度增量（rad）[x,y,z]
    Eigen::Vector3d accel;//加速度计输出的速度增量（m/s）[x,y,z]
};

struct CameraCov {
    Eigen::Matrix3d cov_pos;
    Eigen::Matrix3d cov_euler;
};

struct ImuCov {
    Eigen::Matrix3d cov_pos;
    Eigen::Matrix3d cov_vel;
    Eigen::Matrix3d cov_euler;

    Eigen::Matrix3d cov_gyrbias;
    Eigen::Matrix3d cov_accbias;
    // Eigen::Matrix3d cov_gyrscale;
    // Eigen::Matrix3d cov_accscale;
};

struct ImuNoise {
    Eigen::Vector3d arw;
    Eigen::Vector3d vrw;
    Eigen::Vector3d bg;
    Eigen::Vector3d ba;
    double corrtime;
};

struct ImuState
{
    double timestamp;//GPS周内秒（s）

    Eigen::Vector3d pos{0, 0, 0};
    Eigen::Vector3d vel{0, 0, 0};
    Eigen::Vector3d euler{0, 0, 0};
    Eigen::Quaterniond qbn;
    Eigen::Matrix3d cbn = Eigen::Matrix3d::Zero();

    Eigen::Vector3d gyrbias{0,0,0};
    Eigen::Vector3d accbias{0,0,0};
    // Eigen::Vector3d gyrscale;
    // Eigen::Vector3d accscale;

    ImuNoise noise;
    ImuCov cov;
};

struct SensorResult {
    double timestamp;
    std::unordered_map<int, MatXX> results;
    MatXX covariance;
};

struct NavState
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    double timestamp;           //GPS周内秒（s）
    Eigen::Vector3d pos{0, 0, 0};                       //位置latitude（rad）,Lontitude（rad）,Height（m）
    Eigen::Vector3d vel{0, 0, 0};                  //速度Ve（m/s）,Vn（m/s）,Vu（m/s）
    Eigen::Vector3d euler{0, 0, 0};                  //欧拉角Pitch（rad）,Roll（rad）,Yaw（rad）
    Eigen::Quaterniond qbn;
    Eigen::Matrix3d cbn = Eigen::Matrix3d::Zero();
    Eigen::Vector3d gyrbias{0, 0, 0};
    Eigen::Vector3d accbias{0, 0, 0};
    bool gnss;

    Eigen::Matrix<double, 15, 15> imu_cov;
    void setEmpty(){
        pos.setZero(); 
        vel.setZero();
        euler.setZero();
        cbn.setZero();
        gyrbias.setZero();
        accbias.setZero();
    }

    bool isEmpty() const {
        return pos.isZero() && 
               vel.isZero() && 
               euler.isZero()&&
               cbn.isZero()&&
               gyrbias.isZero()&&
               accbias.isZero();
    }
};


