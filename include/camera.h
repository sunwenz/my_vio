#pragma once

#include "common/commonInclude.h"

using cv::Mat;
using Eigen::Quaterniond;
using Eigen::Vector2d;
using Eigen::Vector3d;

class Camera {

public:
    using Ptr = std::shared_ptr<Camera>;

    Camera() = delete;

    Camera(Mat intrinsic, Mat distortion, const cv::Size &size);

    static Camera::Ptr createCamera(const std::vector<double> &intrinsic, const std::vector<double> &distortion,
                                    const std::vector<int> &size);

    const Mat &cameraMatrix() {
        return intrinsic_;
    }

    void undistortPoints(std::vector<cv::Point2f> &pts);
    void undistortImage(const Mat &src, Mat &dst);
    void distortPoints(std::vector<cv::Point2f> &pts) const;
    void distortPoint(cv::Point2f &pp) const;
    cv::Point2f distortCameraPoint(const Vector3d &pc) const;

    Vector2d reprojectionError(const Pose &pose, const Vector3d &pw, const cv::Point2f &pp) const;

    static Vector3d world2cam(const Vector3d &world, const Pose &pose);
    static Vector3d cam2world(const Vector3d &cam, const Pose &pose);

    Vector3d pixel2cam(const cv::Point2f &pixel) const;
    Vector3d pixel2unitcam(const cv::Point2f &pixel) const;
    cv::Point2f cam2pixel(const Vector3d &cam) const;

    Vector3d pixel2world(const cv::Point2f &pixel, const Pose &pose) const;
    cv::Point2f world2pixel(const Vector3d &world, const Pose &pose) const;

    cv::Size size() const {
        return {width_, height_};
    }

    int width() const {
        return width_;
    }

    int height() const {
        return height_;
    }

    double focalLength() const {
        return (fx_ + fy_) * 0.5;
    }

private:
    Mat distortion_;
    Mat undissrc_, undisdst_;

    double fx_, fy_, cx_, cy_, skew_;
    double k1_, k2_, k3_, p1_, p2_;
    Mat intrinsic_;

    int width_, height_;
};