#pragma once

#include <iostream>
#include <math.h>
#include <Eigen/Core>

/*---------------------WGS84椭球参数----------------------------------*/
#define WGS84_R     (6378137.0) //地球半径(m)
#define	WGS84_F		(1.0 / 298.257223563)	/* Flattening; WGS-84   */
//#define WGS84_Omega (7.2921151467E-5) //地球自转角速率（rad/s）
#define WGS84_Omega (7.292115E-5) //地球自转角速率（rad/s）
#define WGS84_a     (6378137.0) //地球长半轴（m)
#define WGS84_b     (6356752.3142) // 地球椭球短半轴(m)
#define WGS84_e     (0.0818191908426) //地球第一偏心率
#define WGS84_Ge    (9.7803267714)//gravity value at the equator(m3/s2)(新：m/s2)
#define WGS84_Gp    (9.8321863685)//gravity value at the pole(m3/s2)
#define WGS84_GM	(3.986004418E14)//地球引力常数 新加
/*--------------------------------------------------------------------*/

#define PI          (4*atan(1.0))//(3.141592653589793238462643383279) //圆周率
#define R2D         (180.0/PI)     //rad to degree
#define D2R         (PI/180.0)     //degree to rad
#define	MAX_CHAR    1024/2

class Earth{
public:
    /* 函数名：getRN
    作用：由纬度计算卯酉圈半径
    输入：double dLatitude
    输出：
    返回值：dRN
    */
    /*------------------------------------------------------------------------*/
    static double getRN(double lat){
        double W = sqrt(1 - WGS84_e*WGS84_e*sin(lat)*sin(lat));
        double dRN = 0.0;

        dRN = WGS84_a / W;//大地测量学P109
        return (dRN);
    }

    /*------------------------------------------------------------------------*/
    /* 函数名：getRM
    作用：由纬度计算子午圈半径
    输入：double dLatitude
    输出：
    返回值: dRM
    */
    /*------------------------------------------------------------------------*/
    static double getRM(double lat){
        double W = sqrt(1 - WGS84_e*WGS84_e*sin(lat)*sin(lat));

        double dRM = WGS84_a*(1 - WGS84_e*WGS84_e) / (W*W*W);//大地测量学P108
        return (dRM);
    }

    /*------------------------------------------------------------------------*/
    /* 函数名：getW_n_in
    作用：根据位置和速度，求出W_n_ie和W_n_en
    输入：const dMatrix BLH//位置
    const dMatrix Velocity//速度
    输出：dMatrix &W_N_en//n系相对于e系的角速度在n系中的投影向量矩阵
    dMatrix &W_N_ie//e系相对于i系的角速度在n系中的投影向量矩阵
    返回值：无
    */
    /*------------------------------------------------------------------------*/
    static void getW_n_in(const Eigen::Vector3d& BLH, const Eigen::Vector3d& Velocity, Eigen::Vector3d& W_n_ie, Eigen::Vector3d& W_n_en){
        W_n_ie(0,0) = 0.0;
        W_n_ie(1,0) = WGS84_Omega*cos(BLH(0,0));
        W_n_ie(2,0) = WGS84_Omega*sin(BLH(0,0));

        W_n_en(0,0) = -Velocity(1,0) / (getRM(BLH(0,0)) + BLH(2,0));
        W_n_en(1,0) = Velocity(0,0) / (getRN(BLH(0,0)) + BLH(2,0));
        W_n_en(2,0) = Velocity(0,0) * tan(BLH(0,0)) / (getRN(BLH(0,0)) + BLH(2,0));
    }

    /* 函数名：AntimetricM
    作用：计算向量的反对称矩阵(仅适用于3*1矩阵)
    输入：dMatrix Pusy
    输出：
    返回值：AntiM
    */
    /*------------------------------------------------------------------------*/
    Eigen::Matrix3d AntimetricM(Eigen::Vector3d& Pusy){
        Eigen::Matrix3d AntiM  = Eigen::Matrix3d::Zero();

        AntiM(0,0) = 0.0;            AntiM(0,1) = -Pusy(2,0);    AntiM(0,2) = Pusy(1,0);
        AntiM(1,0) = Pusy(2,0);     AntiM(1,1) = 0.0;            AntiM(1,2) = -Pusy(0,0);
        AntiM(2,0) = -Pusy(1,0);    AntiM(2,1) = Pusy(0,0);     AntiM(2,2) = 0.0;

        return (AntiM);
    }


    /*------------------------------------------------------------------------*/
    /* 函数名：xyz2blh
    作用：空间直角坐标转大地坐标
    输入：空间直角坐标xyz,第一片偏心率alfa
    输出：大地坐标（弧度）
    返回值：无
    */
    /*------------------------------------------------------------------------*/
    void xyz2blh(Eigen::Vector3d xyz, Eigen::Vector3d &blh, double alfa, double RE);

    Eigen::Vector3d xyz2blh(const Eigen::Vector3d & xyz);
    /*------------------------------------------------------------------------*/
    /* 函数名：blh2xyz
    作用：大地坐标转空间直角坐标
    输入：大地坐标blh（弧度）,第一片偏心率alfa
    输出：空间直角坐标
    返回值：无
    */
    /*------------------------------------------------------------------------*/
    void blh2xyz(Eigen::Vector3d blh, Eigen::Vector3d &xyz, double alfa, double RE);
    Eigen::Vector3d blh2xyz(const Eigen::Vector3d &blh);

    /**
     *
     * @param xyz_u : 车辆所在位置在地心地固系下的XYZ坐标
     * @param xyz_o ：站心在地心地固系下的XYZ坐标
     * @param enu ：输出在站心坐标系下的坐标
     * 采用右手坐标系，见大地测量学基础P43
     */
    void XYZ2ENU(Eigen::Vector3d &xyz_u, Eigen::Vector3d &xyz_o, Eigen::Vector3d &enu);

    Eigen::Vector3d BLH2ENU(Eigen::Vector3d &blh);

    void enu2blh(const Eigen::Vector3d &enu, const Eigen::Vector3d &blh_o, Eigen::Vector3d &blh);

    Eigen::Matrix3d cne(const Eigen::Vector3d &blh);

    Eigen::Vector3d global2local(const Eigen::Vector3d &origin, const Eigen::Vector3d &global);

    Eigen::Vector3d local2global(const Eigen::Vector3d &origin, const Eigen::Vector3d &local);


};

