#pragma once

#include <Eigen/Core>

class Rotation{
public:

Eigen::Matrix3d Angles2DCM(const Eigen::Vector3d& Attitude)
{
    double p = Attitude[0];//pitch
    double r = Attitude[1];//roll
    double y = Attitude[2];//yaw

    Eigen::Matrix3d DCM = Eigen::Matrix3d::Zero();
    //该公式是北东天坐标系中，规定北偏西为正时的矩阵；
    DCM(0,0) = cos(r)*cos(y) - sin(y)*sin(p)*sin(r);    DCM(0,1) = -1.0*sin(y)*cos(p);    DCM(0,2) = cos(y)*sin(r) + sin(y)*sin(p)*cos(r);
    DCM(1,0) = sin(y)*cos(r) + cos(y)*sin(p)*sin(r);    DCM(1,1) = cos(y)*cos(p);         DCM(1,2) = sin(y)*sin(r) - cos(y)*sin(p)*cos(r);
    DCM(2,0) = -1.0*cos(p)*sin(r);                      DCM(2,1) = sin(p);                DCM(2,2) = cos(p)*cos(r);

    return DCM;
}

Eigen::Vector3d DCM2Angles(const Eigen::Matrix3d& DCM)
{

    Eigen::Vector3d Angles = Eigen::Vector3d::Zero();

    Angles[0] = asin(DCM(2,1));//pitch

    if (fabs(DCM(2,1)) <= 0.999999)
    {
        Angles(1,0) = atan2(-DCM(2,0), DCM(2,2));//roll
        Angles(2,0) = atan2(-DCM(0,1), DCM(1,1));//yaw
    }
    else if (fabs(DCM(2,1)) > 0.999999)
    {
        Angles(1,0) = atan2(DCM(0,2), DCM(0,0));
        Angles(2,0) = 0.0;
    }

    return Angles;
}

/*------------------------------------------------------------------------* /
/* 函数名：AntimetricM
作用：计算向量的反对称矩阵(仅适用于3*1矩阵)
输入：dMatrix Pusy//原矩阵
输出：
返回值：mAntiM//反对称矩阵
*/
/*------------------------------------------------------------------------*/
Mat33 AntimetricM(Vec3 Pusy)
{
	Mat33 AntiM  = Mat33::Zero();

	AntiM(0,0) = 0.0;            AntiM(0,1) = -Pusy(2,0);    AntiM(0,2) = Pusy(1,0);
	AntiM(1,0) = Pusy(2,0);     AntiM(1,1) = 0.0;            AntiM(1,2) = -Pusy(0,0);
	AntiM(2,0) = -Pusy(1,0);    AntiM(2,1) = Pusy(0,0);     AntiM(2,2) = 0.0;

	return (AntiM);
}

};