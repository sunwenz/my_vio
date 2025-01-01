#pragma once

#include <Eigen/Core>

struct GnssData
{
    
};

struct ImuData
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    double timestamp;//GPS周内秒（s）
    Vec3 gyro;//陀螺输出的角速度增量（rad）[x,y,z]
    Vec3 accel;//加速度计输出的速度增量（m/s）[x,y,z]
};

struct CameraCov {
    Mat33 cov_pos;
    Mat33 cov_euler;
};

struct ImuCov {
    Mat33 cov_pos;
    Mat33 cov_vel;
    Mat33 cov_euler;

    Mat33 cov_gyrbias;
    Mat33 cov_accbias;
    // Mat33 cov_gyrscale;
    // Mat33 cov_accscale;
};

struct ImuNoise {
    Vec3 arw;
    Vec3 vrw;
    Vec3 bg;
    Vec3 ba;
    double corrtime;
};

struct ImuState
{
    double timestamp;//GPS周内秒（s）

    Vec3 pos{0, 0, 0};
    Vec3 vel{0, 0, 0};
    Vec3 euler{0, 0, 0};
    Eigen::Quaterniond qbn;
    Mat33 cbn = Eigen::Matrix3d::Zero();

    Vec3 gyrbias{0,0,0};
    Vec3 accbias{0,0,0};
    // Vec3 gyrscale;
    // Vec3 accscale;

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
    Vec3 pos{0, 0, 0};                       //位置latitude（rad）,Lontitude（rad）,Height（m）
    Vec3 vel{0, 0, 0};                  //速度Ve（m/s）,Vn（m/s）,Vu（m/s）
    Vec3 euler{0, 0, 0};                  //欧拉角Pitch（rad）,Roll（rad）,Yaw（rad）
    Eigen::Quaterniond qbn;
    Mat33 cbn = Eigen::Matrix3d::Zero();
    Vec3 gyrbias{0, 0, 0};
    Vec3 accbias{0, 0, 0};
    bool gnss;

    Mat15_15 imu_cov;
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


