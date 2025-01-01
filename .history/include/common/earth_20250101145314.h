#pragma once

#include <iostream>
#include <math.h>

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
    static double getRN(double lat);

    static double getRM(double lat);

    static void getW_n_in(const Vec3 BLH, const Vec3 Velocity, Vec3& W_N_ie, Vec3& W_N_en);

    
}

