#include <iostream>
#include <glog/logging.h>

int main(){
    google::InitGoogleLogging("log.txt");
    
    LOG(INFO) << "This is an info log.";
    LOG(WARNING) << "This is a warning log.";
    LOG(ERROR) << "This is an error log.";

    google::ShutdownGoogleLogging();
    return 0;
}