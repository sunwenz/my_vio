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
    static void getW_n_in(const  BLH, const Vec3 Velocity, Vec3& W_N_ie, Vec3& W_N_en){
        W_n_ie(0,0) = 0.0;
        W_n_ie(1,0) = WGS84_Omega*cos(BLH(0,0));
        W_n_ie(2,0) = WGS84_Omega*sin(BLH(0,0));

        W_n_en(0,0) = -Velocity(1,0) / (getRM(BLH(0,0)) + BLH(2,0));
        W_n_en(1,0) = Velocity(0,0) / (getRN(BLH(0,0)) + BLH(2,0));
        W_n_en(2,0) = Velocity(0,0) * tan(BLH(0,0)) / (getRN(BLH(0,0)) + BLH(2,0));
    }
    /************************************************************************/
    /* -------------以上为纯惯导解算中的通用函数声明----------------------------*/
    /************************************************************************/

    /* 函数名：AntimetricM
    作用：计算向量的反对称矩阵(仅适用于3*1矩阵)
    输入：dMatrix Pusy
    输出：
    返回值：AntiM
    */
    /*------------------------------------------------------------------------*/
    Mat33 AntimetricM(Vec3 Pusy);

    /*------------------------------------------------------------------------*/
    /* 函数名：Cross
    作用：计算两个向量的叉积（仅适用于元素个数为3的矩阵）
    输入：dMatrix A, dMatrix B
    输出：
    返回值：dMatrix C//叉乘结果
    */
    /*------------------------------------------------------------------------*/
    Vec3 Cross(Vec3 A, Vec3 B);

    /*------------------------------------------------------------------------*/
    /* 函数名：QuatNormalize
    作用：归一化四元数
    输入：Quaternion //等效旋转矢量
    输出：无
    返回值：UnitQuat//归一化后的四元数
    */
    /*------------------------------------------------------------------------*/
    Vec4 QuatNormalize(Vec4 Quaternion);

    /*------------------------------------------------------------------------*/
    /* 函数名：QuaternionCross
    作用：计算两个四元数的叉积
    输入：dMatrix A, dMatrix B
    输出：
    返回值：dMatrix C//叉乘结果（叉乘顺序不可调换）
    */
    /*------------------------------------------------------------------------*/
    Vec4 QuaternionCross(Vec4 A, Vec4 B);

    /*------------------------------------------------------------------------*/
    /* 函数名：QuaternionConjugate
    作用：计算该四元数的共轭四元数
    输入：dMatrix A
    输出：
    返回值：dMatrix C//A的共轭四元数
    */
    /*------------------------------------------------------------------------*/
    Vec4 QuaternionConjugate(Vec4 A);

    /*------------------------------------------------------------------------*/
    /* 函数名：xyz2blh
    作用：空间直角坐标转大地坐标
    输入：空间直角坐标xyz,第一片偏心率alfa
    输出：大地坐标（弧度）
    返回值：无
    */
    /*------------------------------------------------------------------------*/
    void xyz2blh(Vec3 xyz, Vec3 &blh, double alfa, double RE);
    Vec3 xyz2blh(const Vec3 & xyz);
    /*------------------------------------------------------------------------*/
    /* 函数名：blh2xyz
    作用：大地坐标转空间直角坐标
    输入：大地坐标blh（弧度）,第一片偏心率alfa
    输出：空间直角坐标
    返回值：无
    */
    /*------------------------------------------------------------------------*/
    void blh2xyz(Vec3 blh, Vec3 &xyz, double alfa, double RE);
    Vec3 blh2xyz(const Vec3 &blh);

    Eigen::Matrix3d GetJ(Eigen::Vector3d blh);
    /**
     *
     * @param xyz_u : 车辆所在位置在地心地固系下的XYZ坐标
     * @param xyz_o ：站心在地心地固系下的XYZ坐标
     * @param enu ：输出在站心坐标系下的坐标
     * 采用右手坐标系，见大地测量学基础P43
     */
    void XYZ2ENU(Vec3 &xyz_u, Vec3 &xyz_o, Vec3 &enu);

    Vec3 BLH2ENU(Vec3 &blh);

    void enu2blh(const Vec3 &enu, const Vec3 &blh_o, Vec3 &blh);

    Mat33 DRi(const Vec3 &blh);

    Mat33 DR(const Vec3 &blh);

    Mat33 DR_ned(const Vec3 &blh);

    Vec3 uvw2enu(double u, double v, double w, double lat0, double lon0);

    Vec3 geodetic2enu(const Vec3 &xyz, const Vec3 &xyz0);

    extern double dot(const double *a, const double *b, int n);

    extern void ecef2pos(const double *r, double *pos);

    Eigen::Matrix3d makeOrthogonal(const Eigen::Matrix3d& R);

    Mat33 cne(const Vec3 &blh);

    Vec3 global2local(const Vec3 &origin, const Vec3 &global);

    Vec3 local2global(const Vec3 &origin, const Vec3 &local);


}

