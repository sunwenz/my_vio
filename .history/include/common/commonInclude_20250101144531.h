#pragma once

/*std*/
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <functional>
#include <thread>
#include <mutex>
#include <ctime>
#include <iomanip>
#include <unordered_set>

/*Eigen*/
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>
using Eigen::Isometry3d;

// double Matrix
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatXX;
typedef Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> MatrixDD_Row;
typedef Eigen::Map<MatXX> Map_DD;
typedef Eigen::Map<MatrixDD_Row> Map_DD_Row;
typedef Eigen::Matrix<double, 8, 3> Mat83;
typedef Eigen::Matrix<double, 6, 6> Mat66;
typedef Eigen::Matrix<double, 5, 3> Mat53;
typedef Eigen::Matrix<double, 4, 3> Mat43;
typedef Eigen::Matrix<double, 4, 2> Mat42;
typedef Eigen::Matrix<double, 3, 3> Mat33;
typedef Eigen::Matrix<double, 2, 2> Mat22;
typedef Eigen::Matrix<double, 8, 8> Mat88;
typedef Eigen::Matrix<double, 7, 7> Mat77;
typedef Eigen::Matrix<double, 4, 9> Mat49;
typedef Eigen::Matrix<double, 8, 9> Mat89;
typedef Eigen::Matrix<double, 9, 4> Mat94;
typedef Eigen::Matrix<double, 9, 8> Mat98;
typedef Eigen::Matrix<double, 1, 6> Mat16;
typedef Eigen::Matrix<double, 8, 1> Mat81;
typedef Eigen::Matrix<double, 1, 8> Mat18;
typedef Eigen::Matrix<double, 9, 1> Mat91;
typedef Eigen::Matrix<double, 1, 9> Mat19;
typedef Eigen::Matrix<double, 1, 2> Mat12;
typedef Eigen::Matrix<double, 2, 6> Mat26;
typedef Eigen::Matrix<double, 8, 4> Mat84;
typedef Eigen::Matrix<double, 4, 8> Mat48;
typedef Eigen::Matrix<double, 4, 4> Mat44;
typedef Eigen::Matrix<double, 3, 4> Mat34;
typedef Eigen::Matrix<double, 3, 6> Mat36;
typedef Eigen::Matrix<double, 6, 15> Mat6_15;
typedef Eigen::Matrix<double, 3, 15> Mat3_15;
typedef Eigen::Matrix<double, 15, 15> Mat15_15;
typedef Eigen::Matrix<double, 21, 21> Mat21_21;

// double vectors
typedef Eigen::Matrix<double, 21, 1> Vec21;
typedef Eigen::Matrix<double, 15, 1> Vec15;
typedef Eigen::Matrix<double, 14, 1> Vec14;
typedef Eigen::Matrix<double, 13, 1> Vec13;
typedef Eigen::Matrix<double, 12, 1> Vec12;
typedef Eigen::Matrix<double, 10, 1> Vec10;
typedef Eigen::Matrix<double, 9, 1> Vec9;
typedef Eigen::Matrix<double, 8, 1> Vec8;
typedef Eigen::Matrix<double, 7, 1> Vec7;
typedef Eigen::Matrix<double, 6, 1> Vec6;
typedef Eigen::Matrix<double, 5, 1> Vec5;
typedef Eigen::Matrix<double, 4, 1> Vec4;
typedef Eigen::Matrix<double, 3, 1> Vec3;
typedef Eigen::Matrix<double, 2, 1> Vec2;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1> VecX;


/*Sophus*/
#include <sophus/se3.hpp>
#include <sophus/so3.hpp>
typedef Sophus::SE3d SE3;
typedef Sophus::SO3d SO3;

#include <ceres/ceres.h>
#include <ceres/rotation.h>

/*OpenCV*/
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/core/eigen.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/features2d/features2d.hpp>
#include <opencv4/opencv2/calib3d/calib3d.hpp>
#include <opencv4/opencv2/video/tracking.hpp>
#include <opencv4/opencv2/dnn.hpp>

