#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1;  // 将日志输出到标准错误流
    LOG(INFO) << "Hello, glog!";
    return 0;
}
